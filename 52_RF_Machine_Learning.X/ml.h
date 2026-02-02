/*
 * File: ml_ml_iris_rf.h
 * Description: IrisRF Classifier for PIC16 microcontrollers
 * Generated: 2026-01-30 02:01:49
 * Source: Converted from micromlgen C++ output
 * 
 * Classifier: Random Forest
 * Trees: 5
 * Features: 4
 * Classes: 3
 */

#ifndef ML_ML_IRIS_RF_H
#define ML_ML_IRIS_RF_H

/*******************************************************************************
 * Configuration
 ******************************************************************************/
#define ML_NUM_FEATURES    4
#define ML_NUM_CLASSES     3
#define ML_NUM_TREES       5

/*******************************************************************************
 * Function: ml_predict
 * Description: Predict class for feature vector
 * Parameters: x - pointer to float array of ML_NUM_FEATURES elements
 * Returns: class index (0 to ML_NUM_CLASSES-1)
 ******************************************************************************/
signed char ml_predict(const float *x)
{
    unsigned char votes[ML_NUM_CLASSES] = { 0 };
    unsigned char classIdx = 0;
    unsigned char maxVotes = 0;
    unsigned char i;
    

                        // tree #1
                        if (x[3] <= 0.75) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[3] <= 1.550000f) {
                                if (x[2] <= 4.75) {
                                    votes[1] += 1;
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }

                            else {
                                if (x[3] <= 1.650000f) {
                                    votes[2] += 1;
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }
                        }

                        // tree #2
                        if (x[2] <= 2.450000f) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[2] <= 4.850000f) {
                                if (x[2] <= 4.75) {
                                    votes[1] += 1;
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }

                            else {
                                if (x[3] <= 1.700000f) {
                                    if (x[0] <= 6.150000f) {
                                        votes[2] += 1;
                                    }

                                    else {
                                        votes[2] += 1;
                                    }
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }
                        }

                        // tree #3
                        if (x[2] <= 2.450000f) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[3] <= 1.700000f) {
                                if (x[1] <= 2.300000f) {
                                    votes[1] += 1;
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        // tree #4
                        if (x[2] <= 2.450000f) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[0] <= 6.25) {
                                if (x[2] <= 4.850000f) {
                                    if (x[3] <= 1.600000f) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }

                            else {
                                if (x[0] <= 7.100000f) {
                                    if (x[0] <= 6.600000f) {
                                        if (x[3] <= 1.650000f) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[2] += 1;
                                        }
                                    }

                                    else {
                                        if (x[2] <= 5.150000f) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[2] += 1;
                                        }
                                    }
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }
                        }

                        // tree #5
                        if (x[3] <= 0.800000f) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[2] <= 4.950000f) {
                                if (x[2] <= 4.850000f) {
                                    if (x[1] <= 2.550000f) {
                                        if (x[3] <= 1.200000f) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }

                            else {
                                if (x[1] <= 2.75) {
                                    if (x[1] <= 2.600000f) {
                                        votes[2] += 1;
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }
                        }

                        /* Find class with most votes */
    maxVotes = votes[0];
    for (i = 1; i < ML_NUM_CLASSES; i++) {
        if (votes[i] > maxVotes) {
            classIdx = i;
            maxVotes = votes[i];
        }
    }
    
    return (signed char)classIdx;
}

#endif /* ML_ML_IRIS_RF_H */
