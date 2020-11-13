import pandas
from Classifier import Classifier

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
