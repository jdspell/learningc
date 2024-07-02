/*
There is not a training stage for the knn algorithm. 
- The training set is our model. KNN is non-parametric meaning no weights!
- Meaning at inference time we refer to all the instances in the dataset to find the k nearest neighbors.
- We can calculate the nearest neighbors for the points in the training set and for new points outside of the test set.

Steps for prediction with KNN:
1. Find the k nearest neighbors according to a predefined similarity metric like euclidean distance.
    - Calculate distances between the point of interests features and all points in the dataset.
    - Sort the points according to the calculated distances.
    - Retain the top k points.
2. Apply a function to get your desired prediction:
    - For regression avg, min, max or mean could be applied.
    - For classification we can just pick the most frequent class in the neighbor group (pick randomly if there is a tie).

Program Flow:
1. Read in model training data (First dummy housing data and then read from csv file).
2. Give an independent variable value (x) and determine nearest neighbors using a defined distance metric.
3. Apply either classification or regression function on the neighbors.
*/

#include <fmt/core.h>
#include <fmt/ranges.h>
#include <cmath>
#include <array>

int CalculateEuclideanDistance(int x_1, int x_2) {
    return sqrt(pow(x_1 - x_2, 2));
}

struct Home {
    int id = -1;
    int sqft = 0;
    int price = -1;
};

struct Distance {
    int homeId = -1;
    int distance = -1;
};

void BubbleSort(Distance* distances, size_t size) {
    for (size_t i=0; i<size; ++i) {
        bool sorted = true;
        for (size_t j=0; j<size-i-1; ++j) {
            if (distances[j].distance > distances[j+1].distance) {
                Distance temp = distances[j];
                distances[j] = distances[j+1];
                distances[j+1] = temp;
                sorted=false;
            }
        }
        if (sorted) {
            break;
        }
    }
}

Home getHomeById(int homeId, Home* homes, size_t size) {
    for (size_t i=0; i<size; ++i) {
        if (homeId == homes[i].id) {
            return homes[i];
        }
    }
    throw std::runtime_error(fmt::format("No home found in getHomeById! for id {}!\n", homeId));
}

int PredictHomePrice(int num_neighbors, Distance* distances, size_t size, Home* homes) {
    if (num_neighbors > size) {
        throw std::runtime_error("Size mismatch. More neighbors than homes available!\n");
    }

    int sum = 0;
    for (size_t i=0; i<num_neighbors; ++i) {
        Home home = getHomeById(distances[i].homeId, homes, size);
        sum += home.price;
    }
    return (sum / num_neighbors);
}

int main() {
    const int kNumberOfHomes = 6;
    // Define the homes where square footage (feature) is used to predict price (label)
    std::array<Home, kNumberOfHomes> homes = {{
        {1, 35, 30000},
        {2, 45, 45000},
        {3, 40, 50000},
        {4, 35, 35000},
        {5, 25, 32500},
        {6, 40, 40000}
    }};

    // Calculate the 3 nearest neighbors for a new home outside of the training set using the home sq ft feature
    const int k = 3;
    int new_home_sqft = 32;
    std::array<Distance, kNumberOfHomes> neighbor_distances;

    for (int j=0; j<kNumberOfHomes; j++) {
        // calculate distance between the two homes according to features (just sqft)
        int distance = CalculateEuclideanDistance(new_home_sqft, homes[j].sqft);
        neighbor_distances[j] = {homes[j].id, distance};
        fmt::print("Home {}: (Sqft: {}, Price: {}) -> Distance: {}\n", j, homes[j].sqft, homes[j].price, neighbor_distances[j].distance);
    }

    // sort the distances and take the ids of the shortest 3
    BubbleSort(neighbor_distances.data(), neighbor_distances.size());
    std::array<int, kNumberOfHomes> sortedHomeIds;
    for (size_t i=0; i<neighbor_distances.size(); ++i) {
        sortedHomeIds[i] = neighbor_distances[i].homeId;
    }
    fmt::print("Homes sorted by distance: {}\n", sortedHomeIds);

    // apply a function to get desired outcome
    // since we are trying to predict home price lets use regression and average the three nearest neighbor values
    int predicted_home_price = PredictHomePrice(k, neighbor_distances.data(), neighbor_distances.size(), homes.data());
    fmt::print("For a home that is {}sqft the predicted price according to our dataset is {}.\n", new_home_sqft, predicted_home_price);
}