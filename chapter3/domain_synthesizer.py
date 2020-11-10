import pandas
import numpy
import matplotlib.pyplot as plt

num_examples = 1000
# Create an empty pandas dataframe 
df = pandas.DataFrame(columns=['att1', 'att2', 'label'])
# Set the random seed so the sequences are reproducible
numpy.random.seed(1)
df['att1'] = numpy.random.rand(num_examples)
df['att2'] = numpy.random.rand(num_examples)
# The shape that I want to classify the examples based on is a circle centered in (0.5, 0.5) with radius 0.5
# So examples within this circle are labled + and examples outside it are labeled -
for row_index, row_data in df.iterrows():
    if (row_data['att1'] - 0.5)**2 + (row_data['att2']-0.5)**2 < 0.25:
        df.loc[row_index,'label'] = '+'
    else:
        df.loc[row_index,'label'] = '-'

# Visualize the synthesized domain usgin a scatter plot
colors = numpy.array(range(0,num_examples), dtype=object)
colors[df['label'] == '+'] = 'r'
colors[df['label'] == '-'] = 'b'
plt.scatter(df['att1'],df['att2'],c=colors)
#plt.show()

# This function adds noise to our labels based on the probabilty given to it
def mutator(row,p):
    random_sample = numpy.random.randint(0,100)
    if random_sample < p:
        if row['label'] == '+':
            row['label'] = '-'
        else:
            row['label'] = '+'
    return row
# Now let's add some noise to the data
# p is explained in question 3 and is the percentage of the examples with changed values 
for p in [5, 10, 15, 20, 25]:
    new_df = df.apply(mutator, axis=1, args=(p,))
    # Write the new data to a file
    new_df.to_csv(str(p)+"%_noise.csv", index=False)
