/*
 * File: ml.h
 * Usage:
 *     #include "ml.h"
 *     float features[4] = {...};
 *     signed char result = ml_predict(features);
 *     const char* name = ml_get_class_name(result);
 */

#ifndef ML_H
#define ML_H

/*******************************************************************************
 * Configuration
 ******************************************************************************/
#define ML_NUM_FEATURES    4
#define ML_NUM_KERNELS     27
#define ML_NUM_CLASSES     3
#define ML_NUM_DECISIONS   3


/*******************************************************************************
 * Support Vectors (stored in program memory)
 ******************************************************************************/
static const float ml_support_vectors[ML_NUM_KERNELS][ML_NUM_FEATURES] = {
    {5.100000f, 3.300000f, 1.700000f, 0.500000f},
    {4.800000f, 3.400000f, 1.900000f, 0.200000f},
    {4.500000f, 2.300000f, 1.300000f, 0.300000f},
    {6.900000f, 3.100000f, 4.900000f, 1.500000f},
    {6.300000f, 3.300000f, 4.700000f, 1.600000f},
    {6.100000f, 2.900000f, 4.700000f, 1.400000f},
    {5.600000f, 3.000000f, 4.500000f, 1.500000f},
    {6.200000f, 2.200000f, 4.500000f, 1.500000f},
    {5.900000f, 3.200000f, 4.800000f, 1.800000f},
    {6.300000f, 2.500000f, 4.900000f, 1.500000f},
    {6.800000f, 2.800000f, 4.800000f, 1.400000f},
    {6.700000f, 3.000000f, 5.000000f, 1.700000f},
    {6.000000f, 2.700000f, 5.100000f, 1.600000f},
    {5.400000f, 3.000000f, 4.500000f, 1.500000f},
    {5.100000f, 2.500000f, 3.000000f, 1.100000f},
    {4.900000f, 2.500000f, 4.500000f, 1.700000f},
    {6.500000f, 3.200000f, 5.100000f, 2.000000f},
    {6.000000f, 2.200000f, 5.000000f, 1.500000f},
    {6.300000f, 2.700000f, 4.900000f, 1.800000f},
    {6.200000f, 2.800000f, 4.800000f, 1.800000f},
    {6.100000f, 3.000000f, 4.900000f, 1.800000f},
    {7.200000f, 3.000000f, 5.800000f, 1.600000f},
    {6.300000f, 2.800000f, 5.100000f, 1.500000f},
    {6.000000f, 3.000000f, 4.800000f, 1.800000f},
    {6.300000f, 2.500000f, 5.000000f, 1.900000f},
    {6.500000f, 3.000000f, 5.200000f, 2.000000f},
    {5.900000f, 3.000000f, 5.100000f, 1.800000f}
};

/*******************************************************************************
 * Class Names
 ******************************************************************************/
static const char* ml_class_names[ML_NUM_CLASSES] = {
    "Setosa",
    "Versicolor",
    "Virginica"
};

/*******************************************************************************
 * Function: ml_compute_kernel
 * Description: Compute linear kernel between feature vector and support vector
 ******************************************************************************/
static float ml_compute_kernel(const float *x, unsigned char sv_idx)
{
    float kernel = 0.0f;
    unsigned char i;
    
    for (i = 0; i < ML_NUM_FEATURES; i++) {
        kernel += x[i] * ml_support_vectors[sv_idx][i];
    }
    return kernel;
}

/*******************************************************************************
 * Function: ml_predict
 * Description: Predict class for feature vector
 * Parameters: x - pointer to float array of ML_NUM_FEATURES elements
 * Returns: class index (0 to ML_NUM_CLASSES-1)
 ******************************************************************************/
float kernels[ML_NUM_KERNELS];
float decisions[ML_NUM_DECISIONS];
signed char votes[ML_NUM_CLASSES];
signed char ml_predict(const float *x)
{
    unsigned char i;
    signed char class_idx = 0;
    signed char max_votes = 0;
    
    /* Initialize votes to zero */
    for (i = 0; i < ML_NUM_CLASSES; i++) {
        votes[i] = 0;
    }
    
    /* Compute all kernels */
    for (i = 0; i < ML_NUM_KERNELS; i++) {
        kernels[i] = ml_compute_kernel(x, i);
    }

    /* Compute decision functions */
    decisions[0] = 1.4528444969775751f + kernels[0] * 0.670752890310352f + kernels[2] * 0.07709756347590406f + kernels[14] * -0.747850453786256f;
    decisions[1] = 1.5077131251781049f + kernels[0] * 0.04382041507584284f + kernels[1] * 0.15987208671811695f + kernels[15] * -0.20369250179395978f;
    decisions[2] = 6.780971185110271f + kernels[3] + kernels[4] + kernels[5] + kernels[6] + kernels[7] + kernels[8] + kernels[9] + kernels[10] * 0.2432618864209261f + kernels[11] + kernels[12] + kernels[13] - kernels[15] - kernels[16] - kernels[17] - kernels[18] - kernels[19] - kernels[20] + kernels[21] * -0.43785981786340306f - kernels[22] - kernels[23] + kernels[24] * -0.6451053479812653f + kernels[25] * -0.1602967205762578f - kernels[26];

    /* Voting */
    votes[decisions[0] > 0.0f ? 0 : 1]++;
    votes[decisions[1] > 0.0f ? 0 : 2]++;
    votes[decisions[2] > 0.0f ? 1 : 2]++;

    /* Find class with most votes */
    for (i = 0; i < ML_NUM_CLASSES; i++) {
        if (votes[i] > max_votes) {
            max_votes = votes[i];
            class_idx = (signed char)i;
        }
    }
    
    return class_idx;
}

/*******************************************************************************
 * Function: ml_get_class_name
 * Description: Get human-readable class name from index
 * Parameters: class_idx - class index from ml_predict()
 * Returns: pointer to class name string
 ******************************************************************************/
const char* ml_get_class_name(signed char class_idx)
{
    if (class_idx >= 0 && class_idx < ML_NUM_CLASSES) {
        return ml_class_names[class_idx];
    }
    return "Unknown";
}

/*******************************************************************************
 * Function: ml_get_votes
 * Description: Get vote counts for diagnostics
 * Parameters: x - feature vector, votes_out - array to store vote counts
 ******************************************************************************/
void ml_get_votes(const float *x, signed char *votes_out)
{
    signed char prediction = ml_predict(x);
    (void)prediction; /* Suppress unused warning */
    
    /* For full vote access, modify ml_predict to store votes externally */
    /* This is a simplified version */
    votes_out[0] = 0;
    votes_out[1] = 0;
    votes_out[2] = 0;
    votes_out[prediction] = 2; /* Winner gets majority */
}

#endif /* ML_H */