import pandas

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

new_example = pandas.DataFrame(data=new_example, index=[0])

print()
k = input("Enter k: ")

# Scale the values
for attrName, attrData in training_set.iteritems():
    if attrData.dtype != object:
        #TODO be ware of division be zero
        attrData = (attrData - attrData.min())/(attrData.max() - attrData.min())


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

print(distances)

# This apply function calculates the distance of each 
#for attrName, attrData in training_set.iteritems():
    #TODO what if the examlpe doesn't contain this attribute
#    distances['distance'] = (attrData - new_example[attrName]).pow(2)
