import pandas

class Classifier:
    # This type of constructor (without any additional arguments is called when user interaction is necessary
    # All examples are stored in domain file. A subset of them is going to be used for training.
    # The rest of them are going to be classified and labeled.
    labeled_dataset = pandas.DataFrame([])
    unlabeled_dataset = pandas.DataFrame([])
    def __init__(self, domain_file, labeled_dataset_location, unlabeled_dataset_location):
        self.labeled_dataset = pandas.read_csv(labeled_dataset_location)
        self.unlabeled_dataset = pandas.read_csv(unlabeled_dataset_location)
        self.labeled_dataset = condition_dataset(self.labeled_dataset)
        self.unlabeled_dataset = condition_dataset(self.unlabeled_dataset)

    # Normalizes the dataset
    def condition_dataset(self, df):
        # TODO: experiment with normalizing only training set and normalizing both the training set and example set.
        # The results should not differ.
        # Iterate columns and scale the values
        for attrName, attrData in df.iteritems():
            if attrData.dtype != object:
                #TODO be ware of division by zero
                #TODO does this even work? because there is no direct modification of df
                attrData = (attrData - attrData.min())/(attrData.max() - attrData.min())
                # Maybe below line should be added:
                #df[attrName] = attrData
        # Return the normalized dataframe
        return df

    def classify_dataset(self, k):
        for row_label, row_data in self.unlabeled_dataset.iterrows():
            row_data['label'] = classify_example(row_data, k)
            # Or maybe:
            #self.unlabeled_dataset.loc[row_label,'label'] = ...
         
    # Here example is a pandas dataframe row
    def classify_example(self, example, k):
        distances = pandas.DataFrame(columns=['distance', 'class_label'])
        def sub_square(col):
            if col.dtype == object:
                try:
                    return col.str.match(pat=new_example[col.name].iloc[0]).astype(float)
                except KeyError:
                    return col
            else: 
                return (col - new_example[col.name].iloc[0]).pow(2)

        distances['class_label'] = training_set['class_label']
        training_set = training_set.drop(['class_label'], axis=1)
        # This apply function subtracts each column from the corresponding new_example attribute and squares it
        training_set = training_set.apply(sub_square, axis=0)
        # This apply function sums all differences and sqrts the result therefore calculating the final distance
        distances['distance'] = training_set.apply(lambda row: row.sum()**(1/2), axis=1)


        # Take the k nearest neighbors
        distances = distances.nsmallest(k, ['distance'])
        distances = distances.reset_index(drop=True)
        d_min = distances['distance'].min()
        d_max = distances['distance'].max()
        # Calculate voting weights, meaning the one that is really close should have mroe to say about new label
        # If all distances are equal then all will have unit weight
        if d_min == d_max:
            distances['distance'] = 1
        else:
            for i in range(0,k):
                distances.loc[i,'distance'] = (d_max - distances.loc[i, 'distance'])/(d_max - d_min)
        # Now let's vote to see which label should be assigned to this new example 
        final_frame = distances.groupby(by=['class_label']).sum().reset_index()
        max_class_index = final_frame['distance'].idxmax()
        class_label = final_frame.loc[max_class_index,'class_label']
        # Return the class label
        return class_label


# In this code I am going to assume that attributes are a mixture of continuous and discrete values
training_set_address = input("Enter the path to training set .csv file: ")
training_set = pandas.read_csv(training_set_address)
print("Training set successfully loaded")

print("Now enter the example you want to classify in the following format:\n \
        <attribute name><space><attribute value><\\n>\n \
enter an empty line when you're finished\n")
str_in = input()
new_example = {}
while len(str_in) != 0:
    attr_val = str_in.split(' ')
    try:
        # Convert everything into float and if it is a string and a ValueError is thrown just ignore it
        new_example[attr_val[0]] = float(attr_val[1])
    except ValueError:
        new_example[attr_val[0]] = attr_val[1]
    str_in = input()

# Convert the new example into a pandas dataframe
new_example = pandas.DataFrame(data=new_example, index=[0])

print()
k = int(input("Enter k: "))
