import pandas

# In this code I am going to assume that attributes are a mixture of continuous and discrete values
training_set_address = input("Enter the path of training set .csv file: ")
df = pandas.read_csv(training_set_address)
print("training set successfully loaded")

k = input("Enter k: ")

# First, scale the values

print(len(df))

