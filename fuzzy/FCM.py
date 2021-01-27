import pandas
import random
import numpy
import matplotlib.pyplot as plt

class FuzzyCMean:
    def __init__(self, dataset):
        self.dataset = dataset
        # n denotes the number of sample points in our dataset
        self.n = len(dataset.index)

    def initialize(self, c):
        # V denotes the set of all cluster centers
        V = {}
        # U denotes the partition matrix
        U = []
        # Select a random index
        rand_index = random.randrange(self.n)
        # Pick random sample points as initial cluster centers 
        for i in range(c):
            # Check if the index has already been selected and keep trying until you find a new one
            while rand_index in V:
                rand_index = random.randrange(self.n)

            V[rand_index] = self.dataset.iloc[rand_index]
            # Initialize the partition matrix with zeroes
            # set the first row to 1s so that the sum of memberships of each sample point to different clusters is 1
            if i == 0:
                U.append([1 for k in range(self.n)])
            else:
                U.append([0 for k in range(self.n)])
        V = list(V.values())
        return V, U

    def find_best_c(self, m, epsilon):
        min_enthropy = 100000
        for c in range(2, 11):
            print ("computing for center " + str(c))
            V, U = self.algorithm(m, c, epsilon)  
            dfU = pandas.DataFrame(U)
            # Calculate enthropy
            enthropy = -1*numpy.sum(dfU.apply(lambda row: numpy.sum(row*numpy.log(row)), axis = 1))/numpy.log(c)
            if enthropy < min_enthropy:
                min_enthropy = enthropy
                best_c = c
                bestV = V

        print("best c: " + str(best_c))
        print("centers: ")
        print(bestV)
        # plot the result
        colors = ['b' for i in range(self.n)]
        for i in range(best_c):
            colors.append('r')
        augmented = self.dataset.append(pandas.DataFrame(bestV))
        plt.scatter(augmented[0], augmented[1], c=colors)
        plt.show()

    def algorithm(self, m, c, epsilon):
        V, U = self.initialize(c)

        def membership_calculator(row):
            # Each row in our dataset is in fact a sample point 
            distance_sum = 0
            distance0flag = False
            # We should keep the distance between this sample point and all the cluster centers
            distance_array = []
            for i in range(c):
                # Calculate the euclidean distances between cluster centers and sample points
                distance = numpy.linalg.norm(row- V[i])
                # distance_sum is going to be the denumerator of the membership formula
                distance_sum += distance
                # If the distance between the sample point and one of the cluster centers is zero then the formula changes so 
                # let's keep a flag about that
                if distance == 0.0:
                    distance0flag = True
                    distance0index = i
                distance_array.append(distance)
            distance_array = numpy.array(distance_array)
            if distance0flag:
                for i in range(c):
                    U[i][row.name] = 0
                U[distance0index][row.name] = 1
            else:
                distance_sum = numpy.sum((1/distance_array) ** (2/(m-1)))
                for i in range(c):
                    # distance_array[i] keeps the euclidean distance between the sample point that we are currently working on
                    # and the ith cluster center
                    U[i][row.name] = ((1/distance_array[i]) ** (2/(m-1)))/distance_sum
        max_distance_change = 1000
        while max_distance_change > epsilon:
            max_distance_change = 0
            self.dataset.apply(membership_calculator, axis=1)
            # Now update the cluster centers based on the new membership functions
            for i in range(c):
                memberships = numpy.array(U[i])
                memberships = memberships ** m
                # This is our denumerator
                mem_sum = memberships.sum()
                old_Vi = V[i]
                V[i] = self.dataset.apply(lambda col: numpy.sum(col*memberships), axis=0)
                V[i] /= mem_sum
                distance_change = numpy.linalg.norm(V[i] - old_Vi)
                if distance_change > max_distance_change:
                    max_distance_change = distance_change
        return V, U
        

df = pandas.read_csv("sample5.csv", header=None)

fcm = FuzzyCMean(df)
fcm.find_best_c(2, 0.00001)
