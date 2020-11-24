# In this code I will try to observe the behavior of k-NN with different k under different levels of noise. 
# All I have to do is to call the classifier in Classifier.py different levels of k on noisy data. 
from Classifier import Classifier
import matplotlib.pyplot as plt
import pandas
import numpy

noise_levels = [5, 10, 15, 20, 25]
domain_fraction = 0.6

# This is a noiseless dataset used to estimated the error rate of the classifier
reference_dataset = pandas.read_csv("datasets/0%_noise.csv")
reference_dataset = reference_dataset.iloc[int(domain_fraction*len(reference_dataset.index)+1):int(len(reference_dataset.index))]
num_to_be_classified = len(reference_dataset)

for p in noise_levels:
    # Read the dataframe
    df = pandas.read_csv("datasets/"+str(p)+"%_noise.csv")
    # Split the dataset into two parts. First part is going to be used to train the classifier
    training_dataset = df.iloc[0:int(domain_fraction*len(df.index))]
    # Second part of dataset is going to be used to relabeled and evaluate the performance of the classifier
    example_dataset = df.iloc[int(domain_fraction*len(df.index)+1):int(len(df.index))]
    # Instantiate the classifier
    classifier = Classifier(training_dataset=training_dataset, example_dataset=example_dataset.copy())
    error_list = [0 for i in range(26)]
    for i in range(1, 26):
        # Classify the training_dataset
        classified_dataset = classifier.classify_dataset(i);
        # Calculate the error by comparing with reference dataframe
        num_errors = reference_dataset['class_label'].eq(classified_dataset['class_label']).sum()
        error_list[i] = 1 - num_errors/num_to_be_classified
    print(error_list)
    plt.plot(range(len(error_list)), error_list)
    plt.xlabel('number of neighbors')
    plt.ylabel('classifier error')
    plt.set_title(str(p)+"% noise")
    plt.tight_layout()
    plt.show()

    '''
    # Visualize the initial and relabeled dataset using a scatter plot to compare the results
    fig, axs = plt.subplots(2)
    colors = numpy.array(range(0,len(classified_dataset.index)), dtype=object)
    colors[classified_dataset['class_label'] == '+'] = 'r'
    colors[classified_dataset['class_label'] == '-'] = 'b'
    axs[0].scatter(classified_dataset['att1'],classified_dataset['att2'],c=colors)
    axs[0].set_title('original with ' + str(p) +'% noise')
    colors[example_dataset['class_label'] == '+'] = 'r'
    colors[example_dataset['class_label'] == '-'] = 'b'
    axs[1].scatter(example_dataset['att1'],example_dataset['att2'],c=colors)
    axs[1].set_title('classified')
    plt.tight_layout()
    plt.savefig("plots/"+str(domain_fraction*100)+"%_trainingset_"+str(p)+"%noise.png")
    '''
