import pandas

''' This class takes two labeled datasets as input, uses one as a training set to relabel and 
    reclassify the other using k-NN (k-nearest neighbors) algorithm with a given k.
'''

class Classifier:
    # This is our training domain   
    labeled_dataset = pandas.DataFrame([])
    # This is the examples that need to be classified
    unlabeled_dataset = pandas.DataFrame([])
    def __init__(self, **kwargs):
        if len(kwargs) < 2:
            raise Exception("Too few arguments")
        for key, value in kwargs.items():
            if key == 'training_dataset':
                self.labeled_dataset = value
            elif key == 'example_dataset':
                self.unlabeled_dataset = value
            elif key == 'training_dataset_location':
                self.labeled_dataset = pandas.read_csv(labeled_dataset_location)
            elif key == 'example_dataset_location':
                self.unlabeled_dataset = pandas.read_csv(unlabeled_dataset_location)
        self.labeled_dataset = self.condition_dataset(self.labeled_dataset)
        self.unlabeled_dataset = self.condition_dataset(self.unlabeled_dataset)
        self.distances = pandas.DataFrame(columns=['distance', 'class_label'])
        self.distances['class_label'] = self.labeled_dataset['class_label']
        # Assuming the class_label is the last column this should remove the class label so it won't count as an attribute
        self.only_atts_dataset = self.labeled_dataset[self.labeled_dataset.columns[0:-1]]
    

    # Normalizes the dataset
    def condition_dataset(self, df):
        # TODO: experiment with normalizing only training set and normalizing both the training set and example set.
        # The results should not differ.
        # Iterate columns and scale the values
        for attrName, attrData in df.iteritems():
            if attrData.dtype != object:
                #TODO be ware of division by zero
                attrData = (attrData - attrData.min())/(attrData.max() - attrData.min())
        # Return the normalized dataframe
        return df

    def classify_dataset(self, k):
        # Make a copy of the unlabeled_data
        unlabeled_dataset_copy = self.unlabeled_dataset
        # Drop the class_label column that might be present in our unlabeled_data
        unlabeled_dataset_copy.drop(['class_label'], axis=1)
        for row_label, row_data in unlabeled_dataset_copy.iterrows():
            # Update the example class label
            unlabeled_dataset_copy.at[row_label,'class_label'] = self.classify_example(row_data, k)
        # Return the now labeled unlabeled_dataset
        return unlabeled_dataset_copy
         

    # Here example is a pandas dataframe row
    def classify_example(self, example, k):

        def sub_square(col):
            if col.dtype == object:
                try:
                    return col.str.match(pat=example[col.name]).astype(float)
                except KeyError:
                    return col
            else: 
                return (col - example[col.name]).pow(2)
        
        # This apply function subtracts each column from the corresponding example attribute and squares it
        attribute_diffs = self.only_atts_dataset.apply(sub_square, axis=0)
        # This apply function sums all differences therefore calculating the final distance
        self.distances['distance'] = attribute_diffs.apply(lambda row: row.sum(), axis=1)


        # Take the k nearest neighbors
        nearest_neighbors = self.distances.nsmallest(k, ['distance'])
        nearest_neighbors = nearest_neighbors.reset_index(drop=True)
        d_min = nearest_neighbors['distance'].min()
        d_max = nearest_neighbors['distance'].max()
        # Calculate voting weights, meaning the one that is really close should have mroe to say about new label
        # If all distances are equal then all will have unit weight
        if d_min == d_max:
            nearest_neighbors['distance'] = 1
        else:
            for i in range(0,k):
                nearest_neighbors.loc[i,'distance'] = (d_max - nearest_neighbors.loc[i, 'distance'])/(d_max - d_min)
        # Now let's vote to see which label should be assigned to this new example 
        final_frame = nearest_neighbors.groupby(by=['class_label']).sum().reset_index()
        max_class_index = final_frame['distance'].idxmax()
        class_label = final_frame.loc[max_class_index,'class_label']
        # Return the class label
        return class_label

