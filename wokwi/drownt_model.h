// Auto-generated TinyML Random Forest Model for ESP32 (v2 - noisy + correlated data)
// Features: [0]=SpO2, [1]=HeartRate, [2]=Temperature, [3]=InWater, [4]=Pitch, [5]=Roll, [6]=IsFaceDown
// Output: output[0]=P(AMAN), output[1]=P(WASPADA), output[2]=P(KRITIS)

#ifndef DROWNT_MODEL_H
#define DROWNT_MODEL_H

#include <string.h>
void add_vectors(double *v1, double *v2, int size, double *result) {
    for(int i = 0; i < size; ++i)
        result[i] = v1[i] + v2[i];
}
void mul_vector_number(double *v1, double num, int size, double *result) {
    for(int i = 0; i < size; ++i)
        result[i] = v1[i] * num;
}
void predict_drownt_status(double * input, double * output) {
    double var0[3];
    double var1[3];
    double var2[3];
    double var3[3];
    double var4[3];
    double var5[3];
    double var6[3];
    double var7[3];
    double var8[3];
    double var9[3];
    double var10[3];
    double var11[3];
    double var12[3];
    double var13[3];
    double var14[3];
    double var15[3];
    if (input[6] <= 0.5) {
        if (input[2] <= 35.97204399108887) {
            if (input[1] <= 86.12173843383789) {
                if (input[2] <= 32.51172637939453) {
                    memcpy(var15, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[4] <= 35.0220947265625) {
                        if (input[2] <= 35.75064468383789) {
                            memcpy(var15, (double[]){0.006622516556291391, 0.8145695364238411, 0.17880794701986755}, 3 * sizeof(double));
                        } else {
                            memcpy(var15, (double[]){0.9655172413793104, 0.034482758620689655, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var15, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            } else {
                if (input[2] <= 34.25573921203613) {
                    if (input[0] <= 91.44700622558594) {
                        if (input[1] <= 88.37003326416016) {
                            memcpy(var15, (double[]){0.0, 0.16666666666666666, 0.8333333333333334}, 3 * sizeof(double));
                        } else {
                            memcpy(var15, (double[]){0.0, 0.010416666666666666, 0.9895833333333334}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[0] <= 91.6350326538086) {
                            memcpy(var15, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var15, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[0] <= 83.65926361083984) {
                        memcpy(var15, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[5] <= 66.61222839355469) {
                            memcpy(var15, (double[]){0.010617760617760617, 0.9797297297297297, 0.009652509652509652}, 3 * sizeof(double));
                        } else {
                            memcpy(var15, (double[]){0.0, 0.375, 0.625}, 3 * sizeof(double));
                        }
                    }
                }
            }
        } else {
            if (input[0] <= 92.13298034667969) {
                if (input[4] <= 22.608908653259277) {
                    memcpy(var15, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                } else {
                    if (input[4] <= 23.701848030090332) {
                        memcpy(var15, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                    } else {
                        memcpy(var15, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    }
                }
            } else {
                if (input[2] <= 36.8884391784668) {
                    if (input[1] <= 95.12812423706055) {
                        if (input[1] <= 85.43696975708008) {
                            memcpy(var15, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var15, (double[]){0.7166666666666667, 0.2833333333333333, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[1] <= 98.38712310791016) {
                            memcpy(var15, (double[]){0.16326530612244897, 0.8367346938775511, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var15, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[3] <= 0.5) {
                        memcpy(var15, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                    } else {
                        if (input[1] <= 89.20537567138672) {
                            memcpy(var15, (double[]){0.9393939393939394, 0.06060606060606061, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var15, (double[]){0.07142857142857142, 0.9285714285714286, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            }
        }
    } else {
        memcpy(var15, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
    }
    double var16[3];
    if (input[1] <= 93.10514450073242) {
        if (input[6] <= 0.5) {
            if (input[3] <= 0.5) {
                if (input[2] <= 35.74292755126953) {
                    if (input[2] <= 32.14821815490723) {
                        memcpy(var16, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[2] <= 35.12345314025879) {
                            memcpy(var16, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var16, (double[]){0.5, 0.5, 0.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[5] <= 32.00855827331543) {
                        if (input[1] <= 88.40382385253906) {
                            memcpy(var16, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var16, (double[]){0.9950248756218906, 0.004975124378109453, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[4] <= 23.583439826965332) {
                            memcpy(var16, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var16, (double[]){0.5, 0.5, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[1] <= 84.73871231079102) {
                    if (input[2] <= 32.51172637939453) {
                        memcpy(var16, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[5] <= -87.94175720214844) {
                            memcpy(var16, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var16, (double[]){0.21787709497206703, 0.664804469273743, 0.11731843575418995}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[1] <= 90.73815536499023) {
                        if (input[4] <= 12.908124446868896) {
                            memcpy(var16, (double[]){0.0707070707070707, 0.7070707070707071, 0.2222222222222222}, 3 * sizeof(double));
                        } else {
                            memcpy(var16, (double[]){0.0, 0.9428571428571428, 0.05714285714285714}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var16, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    }
                }
            }
        } else {
            memcpy(var16, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
        }
    } else {
        if (input[2] <= 34.493595123291016) {
            if (input[3] <= 0.5) {
                if (input[1] <= 142.2716827392578) {
                    if (input[4] <= -0.6021947860717773) {
                        memcpy(var16, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[2] <= 32.64734363555908) {
                            memcpy(var16, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var16, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    memcpy(var16, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            } else {
                if (input[2] <= 34.30666542053223) {
                    memcpy(var16, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[6] <= 0.5) {
                        if (input[0] <= 89.14664077758789) {
                            memcpy(var16, (double[]){0.0, 0.25, 0.75}, 3 * sizeof(double));
                        } else {
                            memcpy(var16, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var16, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            }
        } else {
            if (input[2] <= 37.097707748413086) {
                if (input[6] <= 0.5) {
                    if (input[1] <= 152.32012939453125) {
                        if (input[4] <= 47.03708267211914) {
                            memcpy(var16, (double[]){0.03004891684136967, 0.9573724668064291, 0.012578616352201259}, 3 * sizeof(double));
                        } else {
                            memcpy(var16, (double[]){0.0, 0.25, 0.75}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var16, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                } else {
                    memcpy(var16, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            } else {
                memcpy(var16, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
            }
        }
    }
    add_vectors(var15, var16, 3, var14);
    double var17[3];
    if (input[2] <= 34.61355972290039) {
        if (input[3] <= 0.5) {
            if (input[2] <= 32.49854278564453) {
                memcpy(var17, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
            } else {
                if (input[6] <= 0.5) {
                    if (input[0] <= 79.76315307617188) {
                        memcpy(var17, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        memcpy(var17, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    }
                } else {
                    memcpy(var17, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            }
        } else {
            if (input[4] <= -30.47319984436035) {
                if (input[2] <= 33.79587745666504) {
                    memcpy(var17, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[6] <= 0.5) {
                        if (input[2] <= 33.85951042175293) {
                            memcpy(var17, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var17, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var17, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            } else {
                if (input[2] <= 32.53677558898926) {
                    memcpy(var17, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[0] <= 86.42593383789062) {
                        memcpy(var17, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[6] <= 0.5) {
                            memcpy(var17, (double[]){0.0, 0.9482758620689655, 0.05172413793103448}, 3 * sizeof(double));
                        } else {
                            memcpy(var17, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    }
                }
            }
        }
    } else {
        if (input[1] <= 91.95491027832031) {
            if (input[2] <= 35.85320472717285) {
                if (input[6] <= 0.5) {
                    if (input[3] <= 0.5) {
                        if (input[2] <= 35.17608833312988) {
                            memcpy(var17, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var17, (double[]){0.6666666666666666, 0.2, 0.13333333333333333}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[5] <= -53.81569862365723) {
                            memcpy(var17, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var17, (double[]){0.0, 0.9340659340659341, 0.06593406593406594}, 3 * sizeof(double));
                        }
                    }
                } else {
                    memcpy(var17, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            } else {
                if (input[3] <= 0.5) {
                    if (input[4] <= -30.00629997253418) {
                        memcpy(var17, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    } else {
                        if (input[1] <= 90.96242141723633) {
                            memcpy(var17, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var17, (double[]){0.9534883720930233, 0.046511627906976744, 0.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[1] <= 85.43696975708008) {
                        if (input[4] <= 37.57271766662598) {
                            memcpy(var17, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var17, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[0] <= 92.9255485534668) {
                            memcpy(var17, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var17, (double[]){0.13636363636363635, 0.8636363636363636, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            }
        } else {
            if (input[5] <= -82.36927795410156) {
                memcpy(var17, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
            } else {
                if (input[6] <= 0.5) {
                    if (input[5] <= 65.42760848999023) {
                        if (input[1] <= 94.8299674987793) {
                            memcpy(var17, (double[]){0.4503311258278146, 0.5496688741721855, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var17, (double[]){0.016152716593245228, 0.9757709251101322, 0.008076358296622614}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[1] <= 120.61343765258789) {
                            memcpy(var17, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var17, (double[]){0.0, 0.07692307692307693, 0.9230769230769231}, 3 * sizeof(double));
                        }
                    }
                } else {
                    memcpy(var17, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            }
        }
    }
    add_vectors(var14, var17, 3, var13);
    double var18[3];
    if (input[6] <= 0.5) {
        if (input[3] <= 0.5) {
            if (input[1] <= 99.47819137573242) {
                if (input[1] <= 63.430538177490234) {
                    if (input[0] <= 83.12944793701172) {
                        memcpy(var18, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[2] <= 31.670382499694824) {
                            memcpy(var18, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var18, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[5] <= 39.79872703552246) {
                        if (input[5] <= -53.63231658935547) {
                            memcpy(var18, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var18, (double[]){0.9884809215262779, 0.010079193664506839, 0.0014398848092152627}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[0] <= 93.05081558227539) {
                            memcpy(var18, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var18, (double[]){0.8461538461538461, 0.07692307692307693, 0.07692307692307693}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[4] <= -54.42292022705078) {
                    memcpy(var18, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    memcpy(var18, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                }
            }
        } else {
            if (input[4] <= 46.951101303100586) {
                if (input[1] <= 86.34070205688477) {
                    if (input[2] <= 32.51172637939453) {
                        memcpy(var18, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[2] <= 35.88274383544922) {
                            memcpy(var18, (double[]){0.0, 0.8300653594771242, 0.16993464052287582}, 3 * sizeof(double));
                        } else {
                            memcpy(var18, (double[]){0.94, 0.06, 0.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[0] <= 83.41807556152344) {
                        memcpy(var18, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[2] <= 33.18120574951172) {
                            memcpy(var18, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var18, (double[]){0.005235602094240839, 0.9835452505609574, 0.011219147344801797}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[2] <= 36.310659408569336) {
                    if (input[2] <= 33.923234939575195) {
                        memcpy(var18, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[2] <= 34.20724105834961) {
                            memcpy(var18, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var18, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    memcpy(var18, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                }
            }
        }
    } else {
        memcpy(var18, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
    }
    add_vectors(var13, var18, 3, var12);
    double var19[3];
    if (input[6] <= 0.5) {
        if (input[1] <= 93.10514450073242) {
            if (input[2] <= 35.76328468322754) {
                if (input[4] <= -0.8027094006538391) {
                    if (input[1] <= 73.66735076904297) {
                        if (input[2] <= 32.69338417053223) {
                            memcpy(var19, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var19, (double[]){0.0, 0.7435897435897436, 0.2564102564102564}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[2] <= 32.459739685058594) {
                            memcpy(var19, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var19, (double[]){0.0375, 0.9625, 0.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[1] <= 88.31049728393555) {
                        if (input[2] <= 32.515933990478516) {
                            memcpy(var19, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var19, (double[]){0.012987012987012988, 0.7662337662337663, 0.22077922077922077}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[1] <= 90.27441024780273) {
                            memcpy(var19, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var19, (double[]){0.0, 0.8125, 0.1875}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[2] <= 36.09025764465332) {
                    if (input[2] <= 36.08847999572754) {
                        if (input[3] <= 0.5) {
                            memcpy(var19, (double[]){0.9743589743589743, 0.02564102564102564, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var19, (double[]){0.16, 0.84, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var19, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    }
                } else {
                    if (input[5] <= -41.01776695251465) {
                        if (input[4] <= 6.783649444580078) {
                            memcpy(var19, (double[]){0.6666666666666666, 0.3333333333333333, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var19, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[4] <= -29.81228256225586) {
                            memcpy(var19, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var19, (double[]){0.9738415545590433, 0.026158445440956652, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            }
        } else {
            if (input[0] <= 83.68572235107422) {
                memcpy(var19, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
            } else {
                if (input[2] <= 34.064361572265625) {
                    memcpy(var19, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[2] <= 36.989662170410156) {
                        if (input[3] <= 0.5) {
                            memcpy(var19, (double[]){0.14885496183206107, 0.851145038167939, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var19, (double[]){0.0, 0.9838449111470113, 0.01615508885298869}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[5] <= 33.33494186401367) {
                            memcpy(var19, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var19, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            }
        }
    } else {
        memcpy(var19, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
    }
    add_vectors(var12, var19, 3, var11);
    double var20[3];
    if (input[2] <= 34.61355972290039) {
        if (input[2] <= 32.56361770629883) {
            memcpy(var20, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
        } else {
            if (input[0] <= 89.35181045532227) {
                if (input[0] <= 86.07783126831055) {
                    if (input[6] <= 0.5) {
                        if (input[1] <= 137.35816192626953) {
                            memcpy(var20, (double[]){0.0, 0.05555555555555555, 0.9444444444444444}, 3 * sizeof(double));
                        } else {
                            memcpy(var20, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var20, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                } else {
                    if (input[4] <= -34.092952728271484) {
                        memcpy(var20, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[1] <= 84.81987762451172) {
                            memcpy(var20, (double[]){0.0, 0.7647058823529411, 0.23529411764705882}, 3 * sizeof(double));
                        } else {
                            memcpy(var20, (double[]){0.0, 0.20833333333333334, 0.7916666666666666}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[2] <= 34.36702537536621) {
                    if (input[2] <= 33.93561935424805) {
                        if (input[6] <= 0.5) {
                            memcpy(var20, (double[]){0.0, 0.9746835443037974, 0.02531645569620253}, 3 * sizeof(double));
                        } else {
                            memcpy(var20, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[1] <= 54.83780288696289) {
                            memcpy(var20, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var20, (double[]){0.0, 0.358974358974359, 0.6410256410256411}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[5] <= 56.70994567871094) {
                        if (input[6] <= 0.5) {
                            memcpy(var20, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var20, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var20, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            }
        }
    } else {
        if (input[1] <= 94.6749382019043) {
            if (input[6] <= 0.5) {
                if (input[2] <= 35.86951446533203) {
                    if (input[5] <= -53.81569862365723) {
                        if (input[5] <= -61.87531089782715) {
                            memcpy(var20, (double[]){0.0, 0.25, 0.75}, 3 * sizeof(double));
                        } else {
                            memcpy(var20, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[5] <= 81.15904235839844) {
                            memcpy(var20, (double[]){0.09154929577464789, 0.9014084507042254, 0.007042253521126761}, 3 * sizeof(double));
                        } else {
                            memcpy(var20, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[4] <= -29.819865226745605) {
                        if (input[5] <= 7.889641493558884) {
                            memcpy(var20, (double[]){0.25, 0.75, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var20, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[3] <= 0.5) {
                            memcpy(var20, (double[]){0.9963289280469897, 0.003671071953010279, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var20, (double[]){0.4344262295081967, 0.5655737704918032, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                memcpy(var20, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
            }
        } else {
            if (input[5] <= 65.42760848999023) {
                if (input[5] <= -73.2728385925293) {
                    if (input[0] <= 93.76260757446289) {
                        memcpy(var20, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        memcpy(var20, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    }
                } else {
                    if (input[2] <= 36.989662170410156) {
                        if (input[0] <= 83.4447250366211) {
                            memcpy(var20, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var20, (double[]){0.015827338129496403, 0.9769784172661871, 0.007194244604316547}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[3] <= 0.5) {
                            memcpy(var20, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var20, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[2] <= 35.88332557678223) {
                    if (input[5] <= 75.87178039550781) {
                        if (input[0] <= 87.21927642822266) {
                            memcpy(var20, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var20, (double[]){0.0, 0.6666666666666666, 0.3333333333333333}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var20, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                } else {
                    memcpy(var20, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                }
            }
        }
    }
    add_vectors(var11, var20, 3, var10);
    double var21[3];
    if (input[1] <= 93.10514450073242) {
        if (input[6] <= 0.5) {
            if (input[5] <= 44.34828758239746) {
                if (input[4] <= 26.759562492370605) {
                    if (input[5] <= -41.824270248413086) {
                        if (input[2] <= 35.31142616271973) {
                            memcpy(var21, (double[]){0.0, 0.07017543859649122, 0.9298245614035088}, 3 * sizeof(double));
                        } else {
                            memcpy(var21, (double[]){0.25, 0.75, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[1] <= 65.0841293334961) {
                            memcpy(var21, (double[]){0.0, 0.32978723404255317, 0.6702127659574468}, 3 * sizeof(double));
                        } else {
                            memcpy(var21, (double[]){0.8240684178375076, 0.09957238851557727, 0.07635919364691508}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[2] <= 34.45127487182617) {
                        if (input[2] <= 32.905460357666016) {
                            memcpy(var21, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var21, (double[]){0.0, 0.4, 0.6}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[2] <= 36.28248977661133) {
                            memcpy(var21, (double[]){0.0, 0.8571428571428571, 0.14285714285714285}, 3 * sizeof(double));
                        } else {
                            memcpy(var21, (double[]){0.8666666666666667, 0.13333333333333333, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[2] <= 32.74338150024414) {
                    memcpy(var21, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[5] <= 77.99292373657227) {
                        if (input[2] <= 36.07337188720703) {
                            memcpy(var21, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var21, (double[]){0.3, 0.7, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var21, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            }
        } else {
            memcpy(var21, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
        }
    } else {
        if (input[5] <= 64.90951919555664) {
            if (input[2] <= 34.49807357788086) {
                if (input[2] <= 34.145320892333984) {
                    memcpy(var21, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[6] <= 0.5) {
                        if (input[1] <= 153.18439483642578) {
                            memcpy(var21, (double[]){0.0, 0.9047619047619048, 0.09523809523809523}, 3 * sizeof(double));
                        } else {
                            memcpy(var21, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var21, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            } else {
                if (input[5] <= -73.29350280761719) {
                    if (input[4] <= -36.319454193115234) {
                        if (input[2] <= 36.02354621887207) {
                            memcpy(var21, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var21, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var21, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                } else {
                    if (input[4] <= 49.03798294067383) {
                        if (input[1] <= 94.93354034423828) {
                            memcpy(var21, (double[]){0.43636363636363634, 0.5636363636363636, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var21, (double[]){0.01279317697228145, 0.9573560767590619, 0.029850746268656716}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var21, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            }
        } else {
            if (input[3] <= 0.5) {
                if (input[6] <= 0.5) {
                    memcpy(var21, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                } else {
                    memcpy(var21, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            } else {
                if (input[0] <= 90.70088958740234) {
                    memcpy(var21, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[1] <= 130.93141174316406) {
                        memcpy(var21, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    } else {
                        memcpy(var21, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            }
        }
    }
    add_vectors(var10, var21, 3, var9);
    double var22[3];
    if (input[0] <= 86.36226272583008) {
        if (input[0] <= 83.7629165649414) {
            memcpy(var22, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
        } else {
            if (input[3] <= 0.5) {
                if (input[5] <= 62.39931678771973) {
                    memcpy(var22, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                } else {
                    memcpy(var22, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            } else {
                if (input[0] <= 85.82230758666992) {
                    if (input[5] <= 53.18360900878906) {
                        if (input[4] <= -6.509337902069092) {
                            memcpy(var22, (double[]){0.0, 0.0625, 0.9375}, 3 * sizeof(double));
                        } else {
                            memcpy(var22, (double[]){0.0, 0.38596491228070173, 0.6140350877192983}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var22, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                } else {
                    if (input[0] <= 86.17150497436523) {
                        if (input[4] <= -8.495571613311768) {
                            memcpy(var22, (double[]){0.0, 0.875, 0.125}, 3 * sizeof(double));
                        } else {
                            memcpy(var22, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var22, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            }
        }
    } else {
        if (input[1] <= 93.8486442565918) {
            if (input[3] <= 0.5) {
                if (input[1] <= 63.7021369934082) {
                    memcpy(var22, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[2] <= 35.74310111999512) {
                        if (input[1] <= 71.19620895385742) {
                            memcpy(var22, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var22, (double[]){0.05, 0.3, 0.65}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[0] <= 97.15692138671875) {
                            memcpy(var22, (double[]){0.9922978177150192, 0.007702182284980745, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var22, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[2] <= 32.515933990478516) {
                    memcpy(var22, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[6] <= 0.5) {
                        if (input[4] <= -10.99046277999878) {
                            memcpy(var22, (double[]){0.05357142857142857, 0.9464285714285714, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var22, (double[]){0.23857868020304568, 0.7614213197969543, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var22, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            }
        } else {
            if (input[6] <= 0.5) {
                if (input[2] <= 34.249155044555664) {
                    memcpy(var22, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[3] <= 0.5) {
                        if (input[0] <= 92.3571548461914) {
                            memcpy(var22, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var22, (double[]){0.38461538461538464, 0.6153846153846154, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[5] <= 86.73651885986328) {
                            memcpy(var22, (double[]){0.0, 0.9891891891891892, 0.010810810810810811}, 3 * sizeof(double));
                        } else {
                            memcpy(var22, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                memcpy(var22, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
            }
        }
    }
    add_vectors(var9, var22, 3, var8);
    double var23[3];
    if (input[0] <= 88.53865432739258) {
        if (input[2] <= 35.244869232177734) {
            if (input[2] <= 34.556406021118164) {
                if (input[6] <= 0.5) {
                    if (input[1] <= 143.6005401611328) {
                        if (input[1] <= 126.2557144165039) {
                            memcpy(var23, (double[]){0.0, 0.07339449541284404, 0.926605504587156}, 3 * sizeof(double));
                        } else {
                            memcpy(var23, (double[]){0.0, 0.4, 0.6}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                } else {
                    memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            } else {
                if (input[0] <= 85.12454605102539) {
                    if (input[3] <= 0.5) {
                        if (input[1] <= 117.36537551879883) {
                            memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var23, (double[]){0.0, 0.75, 0.25}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[1] <= 132.27195739746094) {
                            memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var23, (double[]){0.0, 0.01639344262295082, 0.9836065573770492}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[4] <= 32.44717502593994) {
                        if (input[6] <= 0.5) {
                            memcpy(var23, (double[]){0.0, 0.9777777777777777, 0.022222222222222223}, 3 * sizeof(double));
                        } else {
                            memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            }
        } else {
            if (input[0] <= 83.7947769165039) {
                memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
            } else {
                if (input[6] <= 0.5) {
                    if (input[4] <= 36.26475715637207) {
                        memcpy(var23, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    } else {
                        memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                } else {
                    memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            }
        }
    } else {
        if (input[3] <= 0.5) {
            if (input[1] <= 99.43053436279297) {
                if (input[2] <= 35.74292755126953) {
                    if (input[6] <= 0.5) {
                        if (input[0] <= 94.65555953979492) {
                            memcpy(var23, (double[]){0.0, 0.75, 0.25}, 3 * sizeof(double));
                        } else {
                            memcpy(var23, (double[]){0.16666666666666666, 0.16666666666666666, 0.6666666666666666}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                } else {
                    memcpy(var23, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                }
            } else {
                memcpy(var23, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
            }
        } else {
            if (input[1] <= 86.77869415283203) {
                if (input[2] <= 32.53610801696777) {
                    memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[1] <= 68.15335845947266) {
                        if (input[5] <= -8.488877296447754) {
                            memcpy(var23, (double[]){0.0, 0.3333333333333333, 0.6666666666666666}, 3 * sizeof(double));
                        } else {
                            memcpy(var23, (double[]){0.0, 0.7931034482758621, 0.20689655172413793}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[2] <= 35.86545181274414) {
                            memcpy(var23, (double[]){0.0, 0.6206896551724138, 0.3793103448275862}, 3 * sizeof(double));
                        } else {
                            memcpy(var23, (double[]){0.8627450980392157, 0.13725490196078433, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[0] <= 89.88555908203125) {
                    if (input[2] <= 34.43655014038086) {
                        memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[5] <= -109.93311309814453) {
                            memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var23, (double[]){0.0, 0.9753086419753086, 0.024691358024691357}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[4] <= 57.37379837036133) {
                        if (input[1] <= 149.91668701171875) {
                            memcpy(var23, (double[]){0.010335917312661501, 0.9707149009474592, 0.018949181739879417}, 3 * sizeof(double));
                        } else {
                            memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var23, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            }
        }
    }
    add_vectors(var8, var23, 3, var7);
    double var24[3];
    if (input[3] <= 0.5) {
        if (input[0] <= 92.07306289672852) {
            if (input[1] <= 110.11929321289062) {
                if (input[2] <= 32.507408142089844) {
                    memcpy(var24, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[0] <= 85.24236679077148) {
                        memcpy(var24, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[4] <= 16.132495880126953) {
                            memcpy(var24, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var24, (double[]){0.3333333333333333, 0.6666666666666666, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[2] <= 34.168771743774414) {
                    memcpy(var24, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[6] <= 0.5) {
                        memcpy(var24, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    } else {
                        memcpy(var24, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            }
        } else {
            if (input[4] <= -31.58568286895752) {
                memcpy(var24, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
            } else {
                if (input[4] <= 33.15773582458496) {
                    if (input[0] <= 93.12245559692383) {
                        if (input[2] <= 36.09936332702637) {
                            memcpy(var24, (double[]){0.04166666666666667, 0.9166666666666667, 0.04166666666666667}, 3 * sizeof(double));
                        } else {
                            memcpy(var24, (double[]){0.9253731343283582, 0.07462686567164178, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[5] <= 46.804697036743164) {
                            memcpy(var24, (double[]){0.9812593703148426, 0.018740629685157422, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var24, (double[]){0.15384615384615385, 0.6153846153846154, 0.23076923076923078}, 3 * sizeof(double));
                        }
                    }
                } else {
                    memcpy(var24, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                }
            }
        }
    } else {
        if (input[6] <= 0.5) {
            if (input[0] <= 84.78022384643555) {
                if (input[2] <= 35.548282623291016) {
                    if (input[1] <= 138.9942855834961) {
                        if (input[1] <= 137.88352966308594) {
                            memcpy(var24, (double[]){0.0, 0.018867924528301886, 0.9811320754716981}, 3 * sizeof(double));
                        } else {
                            memcpy(var24, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var24, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                } else {
                    if (input[5] <= -39.8261775970459) {
                        memcpy(var24, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    } else {
                        if (input[4] <= 8.055613040924072) {
                            memcpy(var24, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var24, (double[]){0.0, 0.6666666666666666, 0.3333333333333333}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[4] <= 47.03708267211914) {
                    if (input[4] <= -47.08615303039551) {
                        if (input[2] <= 34.9799861907959) {
                            memcpy(var24, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var24, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[1] <= 86.34070205688477) {
                            memcpy(var24, (double[]){0.10747663551401869, 0.3060747663551402, 0.5864485981308412}, 3 * sizeof(double));
                        } else {
                            memcpy(var24, (double[]){0.0073475385745775165, 0.97060984570169, 0.02204261572373255}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[1] <= 111.58263397216797) {
                        memcpy(var24, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    } else {
                        if (input[0] <= 86.31084442138672) {
                            memcpy(var24, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var24, (double[]){0.0, 0.25, 0.75}, 3 * sizeof(double));
                        }
                    }
                }
            }
        } else {
            memcpy(var24, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
        }
    }
    add_vectors(var7, var24, 3, var6);
    double var25[3];
    if (input[0] <= 86.34547424316406) {
        if (input[3] <= 0.5) {
            if (input[6] <= 0.5) {
                if (input[2] <= 35.8347053527832) {
                    if (input[4] <= 26.897096633911133) {
                        if (input[5] <= 109.89780044555664) {
                            memcpy(var25, (double[]){0.0, 0.8333333333333334, 0.16666666666666666}, 3 * sizeof(double));
                        } else {
                            memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                } else {
                    memcpy(var25, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                }
            } else {
                memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
            }
        } else {
            if (input[0] <= 86.045654296875) {
                if (input[2] <= 35.86558723449707) {
                    if (input[2] <= 35.2436580657959) {
                        if (input[2] <= 34.426025390625) {
                            memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var25, (double[]){0.0, 0.02564102564102564, 0.9743589743589743}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[0] <= 83.69454956054688) {
                            memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var25, (double[]){0.0, 0.7272727272727273, 0.2727272727272727}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[2] <= 35.9249267578125) {
                        memcpy(var25, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    } else {
                        if (input[6] <= 0.5) {
                            memcpy(var25, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[0] <= 86.19868850708008) {
                    if (input[2] <= 34.012672424316406) {
                        memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        memcpy(var25, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    }
                } else {
                    memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            }
        }
    } else {
        if (input[1] <= 93.26068115234375) {
            if (input[3] <= 0.5) {
                if (input[1] <= 63.723541259765625) {
                    if (input[4] <= 1.065647929906845) {
                        memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[1] <= 62.06126403808594) {
                            memcpy(var25, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[2] <= 35.17608833312988) {
                        if (input[2] <= 32.28771686553955) {
                            memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var25, (double[]){0.0, 0.8333333333333334, 0.16666666666666666}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[1] <= 85.73735046386719) {
                            memcpy(var25, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var25, (double[]){0.987460815047022, 0.012539184952978056, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[6] <= 0.5) {
                    if (input[2] <= 32.515933990478516) {
                        memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[1] <= 83.40727996826172) {
                            memcpy(var25, (double[]){0.24390243902439024, 0.7560975609756098, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var25, (double[]){0.0851063829787234, 0.9148936170212766, 0.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            }
        } else {
            if (input[2] <= 34.14934730529785) {
                memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
            } else {
                if (input[1] <= 96.5550651550293) {
                    if (input[4] <= 16.634065628051758) {
                        if (input[2] <= 36.1236515045166) {
                            memcpy(var25, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var25, (double[]){0.8333333333333334, 0.16666666666666666, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[3] <= 0.5) {
                            memcpy(var25, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var25, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[5] <= -82.02902603149414) {
                        memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[5] <= 77.45121765136719) {
                            memcpy(var25, (double[]){0.010408921933085501, 0.9724907063197026, 0.017100371747211896}, 3 * sizeof(double));
                        } else {
                            memcpy(var25, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    }
                }
            }
        }
    }
    add_vectors(var6, var25, 3, var5);
    double var26[3];
    if (input[2] <= 34.556406021118164) {
        if (input[0] <= 89.8501968383789) {
            if (input[6] <= 0.5) {
                if (input[5] <= 68.21126556396484) {
                    if (input[3] <= 0.5) {
                        if (input[0] <= 87.94443130493164) {
                            memcpy(var26, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var26, (double[]){0.0, 0.75, 0.25}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[0] <= 86.41498184204102) {
                            memcpy(var26, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var26, (double[]){0.0, 0.2, 0.8}, 3 * sizeof(double));
                        }
                    }
                } else {
                    memcpy(var26, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            } else {
                memcpy(var26, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
            }
        } else {
            if (input[0] <= 97.73849105834961) {
                if (input[6] <= 0.5) {
                    if (input[1] <= 88.31049728393555) {
                        if (input[5] <= 63.69658279418945) {
                            memcpy(var26, (double[]){0.0, 0.3037974683544304, 0.6962025316455697}, 3 * sizeof(double));
                        } else {
                            memcpy(var26, (double[]){0.0, 0.8571428571428571, 0.14285714285714285}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[2] <= 33.40948677062988) {
                            memcpy(var26, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var26, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    memcpy(var26, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            } else {
                if (input[2] <= 31.529934883117676) {
                    memcpy(var26, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    memcpy(var26, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                }
            }
        }
    } else {
        if (input[3] <= 0.5) {
            if (input[0] <= 92.35076904296875) {
                if (input[5] <= -53.526662826538086) {
                    if (input[2] <= 35.93107604980469) {
                        memcpy(var26, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        memcpy(var26, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    }
                } else {
                    if (input[6] <= 0.5) {
                        if (input[1] <= 94.5374984741211) {
                            memcpy(var26, (double[]){0.6666666666666666, 0.25, 0.08333333333333333}, 3 * sizeof(double));
                        } else {
                            memcpy(var26, (double[]){0.0, 0.9873417721518988, 0.012658227848101266}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var26, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            } else {
                if (input[2] <= 35.81498146057129) {
                    if (input[5] <= 14.155675888061523) {
                        if (input[4] <= 9.281151294708252) {
                            memcpy(var26, (double[]){0.08, 0.92, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var26, (double[]){0.5, 0.5, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var26, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    }
                } else {
                    if (input[0] <= 93.30081176757812) {
                        if (input[1] <= 104.62272644042969) {
                            memcpy(var26, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var26, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[5] <= 45.81867790222168) {
                            memcpy(var26, (double[]){0.9910380881254668, 0.008961911874533234, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var26, (double[]){0.5625, 0.4375, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            }
        } else {
            if (input[1] <= 148.88948822021484) {
                if (input[1] <= 84.40145492553711) {
                    if (input[1] <= 63.8038215637207) {
                        if (input[2] <= 34.636287689208984) {
                            memcpy(var26, (double[]){0.0, 0.3333333333333333, 0.6666666666666666}, 3 * sizeof(double));
                        } else {
                            memcpy(var26, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[0] <= 93.18779754638672) {
                            memcpy(var26, (double[]){0.0, 0.5, 0.5}, 3 * sizeof(double));
                        } else {
                            memcpy(var26, (double[]){0.7959183673469388, 0.20408163265306123, 0.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[0] <= 84.67753219604492) {
                        if (input[5] <= 54.99726486206055) {
                            memcpy(var26, (double[]){0.0, 0.1388888888888889, 0.8611111111111112}, 3 * sizeof(double));
                        } else {
                            memcpy(var26, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[2] <= 37.12756538391113) {
                            memcpy(var26, (double[]){0.004477611940298508, 0.9649253731343284, 0.030597014925373135}, 3 * sizeof(double));
                        } else {
                            memcpy(var26, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[2] <= 36.00866508483887) {
                    if (input[4] <= -6.506856441497803) {
                        if (input[0] <= 87.3663330078125) {
                            memcpy(var26, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var26, (double[]){0.0, 0.7142857142857143, 0.2857142857142857}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var26, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                } else {
                    memcpy(var26, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                }
            }
        }
    }
    add_vectors(var5, var26, 3, var4);
    double var27[3];
    if (input[6] <= 0.5) {
        if (input[1] <= 93.26655197143555) {
            if (input[2] <= 35.75952339172363) {
                if (input[0] <= 96.54283905029297) {
                    if (input[5] <= -64.1302375793457) {
                        if (input[4] <= 31.512907028198242) {
                            memcpy(var27, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var27, (double[]){0.0, 0.25, 0.75}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[3] <= 0.5) {
                            memcpy(var27, (double[]){0.0, 0.6551724137931034, 0.3448275862068966}, 3 * sizeof(double));
                        } else {
                            memcpy(var27, (double[]){0.0, 0.35391923990498814, 0.6460807600950119}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[2] <= 32.42648124694824) {
                        memcpy(var27, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        memcpy(var27, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    }
                }
            } else {
                if (input[2] <= 35.958322525024414) {
                    if (input[3] <= 0.5) {
                        if (input[0] <= 95.4380111694336) {
                            memcpy(var27, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var27, (double[]){0.7894736842105263, 0.21052631578947367, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var27, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    }
                } else {
                    if (input[3] <= 0.5) {
                        memcpy(var27, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                    } else {
                        if (input[5] <= -24.2869873046875) {
                            memcpy(var27, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var27, (double[]){0.5753424657534246, 0.4246575342465753, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            }
        } else {
            if (input[0] <= 83.68572235107422) {
                memcpy(var27, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
            } else {
                if (input[1] <= 96.5550651550293) {
                    if (input[3] <= 0.5) {
                        if (input[2] <= 35.75426483154297) {
                            memcpy(var27, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var27, (double[]){0.9795918367346939, 0.02040816326530612, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var27, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    }
                } else {
                    if (input[1] <= 152.9396209716797) {
                        if (input[2] <= 34.241533279418945) {
                            memcpy(var27, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var27, (double[]){0.00680786686838124, 0.9780635400907716, 0.015128593040847202}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var27, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            }
        }
    } else {
        memcpy(var27, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
    }
    add_vectors(var4, var27, 3, var3);
    double var28[3];
    if (input[0] <= 86.045654296875) {
        if (input[6] <= 0.5) {
            if (input[3] <= 0.5) {
                if (input[4] <= 36.196184158325195) {
                    if (input[1] <= 91.76990127563477) {
                        memcpy(var28, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        memcpy(var28, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    }
                } else {
                    memcpy(var28, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            } else {
                if (input[5] <= -50.227230072021484) {
                    memcpy(var28, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[0] <= 83.68572235107422) {
                        memcpy(var28, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[4] <= -43.56508445739746) {
                            memcpy(var28, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var28, (double[]){0.0, 0.7297297297297297, 0.2702702702702703}, 3 * sizeof(double));
                        }
                    }
                }
            }
        } else {
            memcpy(var28, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
        }
    } else {
        if (input[2] <= 35.9797477722168) {
            if (input[5] <= -72.51976013183594) {
                memcpy(var28, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
            } else {
                if (input[1] <= 86.71780014038086) {
                    if (input[6] <= 0.5) {
                        if (input[2] <= 32.515933990478516) {
                            memcpy(var28, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var28, (double[]){0.24324324324324326, 0.7567567567567568, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var28, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                } else {
                    if (input[6] <= 0.5) {
                        if (input[2] <= 34.241533279418945) {
                            memcpy(var28, (double[]){0.0, 0.11764705882352941, 0.8823529411764706}, 3 * sizeof(double));
                        } else {
                            memcpy(var28, (double[]){0.009354536950420954, 0.9859681945743686, 0.004677268475210477}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var28, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            }
        } else {
            if (input[0] <= 92.35821533203125) {
                if (input[2] <= 37.038564682006836) {
                    if (input[3] <= 0.5) {
                        if (input[0] <= 92.08585739135742) {
                            memcpy(var28, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var28, (double[]){0.6666666666666666, 0.3333333333333333, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var28, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    }
                } else {
                    memcpy(var28, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                }
            } else {
                if (input[5] <= 36.07470703125) {
                    if (input[5] <= -31.01864528656006) {
                        if (input[5] <= -41.38996696472168) {
                            memcpy(var28, (double[]){0.0784313725490196, 0.9215686274509803, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var28, (double[]){0.5294117647058824, 0.47058823529411764, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[3] <= 0.5) {
                            memcpy(var28, (double[]){0.9850157728706624, 0.01498422712933754, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var28, (double[]){0.20074349442379183, 0.7992565055762082, 0.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[3] <= 0.5) {
                        if (input[2] <= 36.420888900756836) {
                            memcpy(var28, (double[]){0.1111111111111111, 0.8888888888888888, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var28, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[4] <= 13.824975967407227) {
                            memcpy(var28, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var28, (double[]){0.10526315789473684, 0.8947368421052632, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            }
        }
    }
    add_vectors(var3, var28, 3, var2);
    double var29[3];
    if (input[1] <= 93.31415557861328) {
        if (input[2] <= 35.75952339172363) {
            if (input[6] <= 0.5) {
                if (input[0] <= 97.73849105834961) {
                    if (input[5] <= -55.93830108642578) {
                        if (input[4] <= 18.873560905456543) {
                            memcpy(var29, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var29, (double[]){0.0, 0.0625, 0.9375}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[2] <= 32.50641441345215) {
                            memcpy(var29, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var29, (double[]){0.005847953216374269, 0.9064327485380117, 0.08771929824561403}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[1] <= 70.4942741394043) {
                        if (input[1] <= 54.65290069580078) {
                            memcpy(var29, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var29, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var29, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    }
                }
            } else {
                memcpy(var29, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
            }
        } else {
            if (input[3] <= 0.5) {
                if (input[0] <= 95.70894622802734) {
                    memcpy(var29, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                } else {
                    if (input[4] <= -29.29576587677002) {
                        memcpy(var29, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    } else {
                        if (input[4] <= 25.821829795837402) {
                            memcpy(var29, (double[]){1.0, 0.0, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var29, (double[]){0.875, 0.125, 0.0}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[6] <= 0.5) {
                    if (input[2] <= 36.7036018371582) {
                        if (input[2] <= 36.05825233459473) {
                            memcpy(var29, (double[]){0.034482758620689655, 0.9655172413793104, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var29, (double[]){0.3235294117647059, 0.6764705882352942, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        if (input[0] <= 99.67194747924805) {
                            memcpy(var29, (double[]){0.9117647058823529, 0.08823529411764706, 0.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var29, (double[]){0.4, 0.6, 0.0}, 3 * sizeof(double));
                        }
                    }
                } else {
                    memcpy(var29, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                }
            }
        }
    } else {
        if (input[2] <= 34.493595123291016) {
            if (input[0] <= 92.46608352661133) {
                if (input[0] <= 86.04666137695312) {
                    if (input[2] <= 34.426025390625) {
                        memcpy(var29, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    } else {
                        if (input[0] <= 83.42369079589844) {
                            memcpy(var29, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        } else {
                            memcpy(var29, (double[]){0.0, 0.6, 0.4}, 3 * sizeof(double));
                        }
                    }
                } else {
                    if (input[0] <= 86.18381881713867) {
                        memcpy(var29, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    } else {
                        if (input[6] <= 0.5) {
                            memcpy(var29, (double[]){0.0, 0.52, 0.48}, 3 * sizeof(double));
                        } else {
                            memcpy(var29, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                        }
                    }
                }
            } else {
                if (input[1] <= 129.9957389831543) {
                    if (input[6] <= 0.5) {
                        memcpy(var29, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                    } else {
                        memcpy(var29, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                } else {
                    memcpy(var29, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                }
            }
        } else {
            if (input[4] <= 47.03708267211914) {
                if (input[0] <= 83.8433952331543) {
                    memcpy(var29, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    if (input[6] <= 0.5) {
                        if (input[2] <= 36.88766288757324) {
                            memcpy(var29, (double[]){0.022253129346314328, 0.9728789986091795, 0.0048678720445062594}, 3 * sizeof(double));
                        } else {
                            memcpy(var29, (double[]){0.7307692307692307, 0.2692307692307692, 0.0}, 3 * sizeof(double));
                        }
                    } else {
                        memcpy(var29, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                    }
                }
            } else {
                if (input[0] <= 90.80906295776367) {
                    memcpy(var29, (double[]){0.0, 0.0, 1.0}, 3 * sizeof(double));
                } else {
                    memcpy(var29, (double[]){0.0, 1.0, 0.0}, 3 * sizeof(double));
                }
            }
        }
    }
    add_vectors(var2, var29, 3, var1);
    mul_vector_number(var1, 0.06666666666666667, 3, var0);
    memcpy(output, var0, 3 * sizeof(double));
}


#endif // DROWNT_MODEL_H
