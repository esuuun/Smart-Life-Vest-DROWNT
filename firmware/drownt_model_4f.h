#ifndef DROWNT_MODEL_4F_H
#define DROWNT_MODEL_4F_H

// Auto-generated TinyML Random Forest Model (n=10, depth=6)
// Input array: input[0]=SpO2, input[1]=HR, input[2]=WaterWaist, input[3]=WaterNeck
// Output: prob[0]=ProbAman, prob[1]=ProbWaspada, prob[2]=ProbKritis

#include <string.h>
static inline void set_vec3(double *arr, double a, double b, double c) {
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
}
void add_vectors(double *v1, double *v2, int size, double *result) {
    for(int i = 0; i < size; ++i)
        result[i] = v1[i] + v2[i];
}
void mul_vector_number(double *v1, double num, int size, double *result) {
    for(int i = 0; i < size; ++i)
        result[i] = v1[i] * num;
}
void predict_drownt(double * input, double * output) {
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
    if (input[3] <= 16.912599563598633) {
        if (input[0] <= 96.21861267089844) {
            if (input[0] <= 87.0) {
                set_vec3(var10, 0.0, 0.0, 1.0);
            } else {
                if (input[0] <= 95.11266326904297) {
                    if (input[2] <= 19.601022243499756) {
                        set_vec3(var10, 1.0, 0.0, 0.0);
                    } else {
                        set_vec3(var10, 0.0, 1.0, 0.0);
                    }
                } else {
                    if (input[2] <= 24.879436492919922) {
                        set_vec3(var10, 1.0, 0.0, 0.0);
                    } else {
                        set_vec3(var10, 0.0, 1.0, 0.0);
                    }
                }
            }
        } else {
            if (input[0] <= 98.00188827514648) {
                if (input[2] <= 27.502238750457764) {
                    set_vec3(var10, 1.0, 0.0, 0.0);
                } else {
                    set_vec3(var10, 0.0, 1.0, 0.0);
                }
            } else {
                set_vec3(var10, 1.0, 0.0, 0.0);
            }
        }
    } else {
        if (input[0] <= 93.27442932128906) {
            if (input[3] <= 22.580631256103516) {
                if (input[3] <= 22.473576545715332) {
                    if (input[3] <= 18.08793830871582) {
                        if (input[2] <= 72.53097534179688) {
                            set_vec3(var10, 0.0, 0.6666666666666666, 0.3333333333333333);
                        } else {
                            set_vec3(var10, 0.0, 0.0, 1.0);
                        }
                    } else {
                        set_vec3(var10, 0.0, 0.0, 1.0);
                    }
                } else {
                    set_vec3(var10, 0.0, 1.0, 0.0);
                }
            } else {
                set_vec3(var10, 0.0, 0.0, 1.0);
            }
        } else {
            set_vec3(var10, 0.0, 1.0, 0.0);
        }
    }
    double var11[3];
    if (input[2] <= 22.15372085571289) {
        if (input[3] <= 32.90376853942871) {
            set_vec3(var11, 1.0, 0.0, 0.0);
        } else {
            set_vec3(var11, 0.0, 0.0, 1.0);
        }
    } else {
        if (input[0] <= 88.97673416137695) {
            set_vec3(var11, 0.0, 0.0, 1.0);
        } else {
            if (input[3] <= 30.841583251953125) {
                set_vec3(var11, 0.0, 1.0, 0.0);
            } else {
                set_vec3(var11, 0.0, 0.0, 1.0);
            }
        }
    }
    add_vectors(var10, var11, 3, var9);
    double var12[3];
    if (input[2] <= 17.524185180664062) {
        if (input[3] <= 34.53039360046387) {
            set_vec3(var12, 1.0, 0.0, 0.0);
        } else {
            set_vec3(var12, 0.0, 0.0, 1.0);
        }
    } else {
        if (input[3] <= 16.03221607208252) {
            if (input[3] <= 6.479576349258423) {
                if (input[0] <= 85.88521194458008) {
                    set_vec3(var12, 0.0, 0.0, 1.0);
                } else {
                    set_vec3(var12, 0.0, 1.0, 0.0);
                }
            } else {
                if (input[1] <= 130.46627807617188) {
                    if (input[0] <= 87.0) {
                        set_vec3(var12, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var12, 0.0, 1.0, 0.0);
                    }
                } else {
                    if (input[0] <= 87.07321166992188) {
                        set_vec3(var12, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var12, 0.0, 1.0, 0.0);
                    }
                }
            }
        } else {
            if (input[3] <= 17.98166847229004) {
                if (input[2] <= 70.91705703735352) {
                    set_vec3(var12, 0.0, 1.0, 0.0);
                } else {
                    if (input[1] <= 151.16582489013672) {
                        if (input[0] <= 88.50648880004883) {
                            set_vec3(var12, 0.0, 0.0, 1.0);
                        } else {
                            set_vec3(var12, 0.0, 1.0, 0.0);
                        }
                    } else {
                        set_vec3(var12, 0.0, 1.0, 0.0);
                    }
                }
            } else {
                if (input[0] <= 93.39421844482422) {
                    if (input[3] <= 22.580631256103516) {
                        if (input[1] <= 100.38983154296875) {
                            set_vec3(var12, 0.0, 1.0, 0.0);
                        } else {
                            set_vec3(var12, 0.0, 0.019230769230769232, 0.9807692307692307);
                        }
                    } else {
                        set_vec3(var12, 0.0, 0.0, 1.0);
                    }
                } else {
                    set_vec3(var12, 0.0, 1.0, 0.0);
                }
            }
        }
    }
    add_vectors(var9, var12, 3, var8);
    double var13[3];
    if (input[2] <= 22.15372085571289) {
        if (input[0] <= 93.68829345703125) {
            set_vec3(var13, 0.0, 0.0, 1.0);
        } else {
            set_vec3(var13, 1.0, 0.0, 0.0);
        }
    } else {
        if (input[1] <= 82.42146301269531) {
            set_vec3(var13, 0.0, 0.0, 1.0);
        } else {
            if (input[3] <= 16.034945487976074) {
                if (input[0] <= 87.0) {
                    set_vec3(var13, 0.0, 0.0, 1.0);
                } else {
                    set_vec3(var13, 0.0, 1.0, 0.0);
                }
            } else {
                if (input[0] <= 93.39421844482422) {
                    if (input[3] <= 18.041781425476074) {
                        if (input[0] <= 87.14458465576172) {
                            set_vec3(var13, 0.0, 0.0, 1.0);
                        } else {
                            set_vec3(var13, 0.0, 1.0, 0.0);
                        }
                    } else {
                        if (input[1] <= 96.99796295166016) {
                            set_vec3(var13, 0.0, 0.2, 0.8);
                        } else {
                            set_vec3(var13, 0.0, 0.0, 1.0);
                        }
                    }
                } else {
                    set_vec3(var13, 0.0, 1.0, 0.0);
                }
            }
        }
    }
    add_vectors(var8, var13, 3, var7);
    double var14[3];
    if (input[3] <= 15.099550247192383) {
        if (input[2] <= 22.157761573791504) {
            set_vec3(var14, 1.0, 0.0, 0.0);
        } else {
            if (input[1] <= 135.52609252929688) {
                if (input[2] <= 81.87349700927734) {
                    if (input[0] <= 86.6869125366211) {
                        set_vec3(var14, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var14, 0.0, 1.0, 0.0);
                    }
                } else {
                    if (input[0] <= 87.0) {
                        set_vec3(var14, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var14, 0.0, 1.0, 0.0);
                    }
                }
            } else {
                if (input[3] <= 6.361717700958252) {
                    if (input[0] <= 84.9917106628418) {
                        set_vec3(var14, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var14, 0.0, 1.0, 0.0);
                    }
                } else {
                    if (input[1] <= 155.33686065673828) {
                        if (input[3] <= 7.322883367538452) {
                            set_vec3(var14, 0.0, 0.0, 1.0);
                        } else {
                            set_vec3(var14, 0.0, 0.5189873417721519, 0.4810126582278481);
                        }
                    } else {
                        if (input[1] <= 158.06736755371094) {
                            set_vec3(var14, 0.0, 0.2, 0.8);
                        } else {
                            set_vec3(var14, 0.0, 0.0, 1.0);
                        }
                    }
                }
            }
        }
    } else {
        if (input[0] <= 93.27442932128906) {
            if (input[3] <= 18.93958568572998) {
                if (input[2] <= 62.07185745239258) {
                    set_vec3(var14, 0.0, 1.0, 0.0);
                } else {
                    if (input[0] <= 87.51628112792969) {
                        set_vec3(var14, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var14, 0.0, 1.0, 0.0);
                    }
                }
            } else {
                if (input[3] <= 22.70266056060791) {
                    if (input[2] <= 65.60127639770508) {
                        set_vec3(var14, 0.0, 1.0, 0.0);
                    } else {
                        set_vec3(var14, 0.0, 0.0, 1.0);
                    }
                } else {
                    set_vec3(var14, 0.0, 0.0, 1.0);
                }
            }
        } else {
            set_vec3(var14, 0.0, 1.0, 0.0);
        }
    }
    add_vectors(var7, var14, 3, var6);
    double var15[3];
    if (input[2] <= 17.524185180664062) {
        if (input[0] <= 93.68829345703125) {
            set_vec3(var15, 0.0, 0.0, 1.0);
        } else {
            set_vec3(var15, 1.0, 0.0, 0.0);
        }
    } else {
        if (input[0] <= 88.99232864379883) {
            set_vec3(var15, 0.0, 0.0, 1.0);
        } else {
            if (input[3] <= 31.574199676513672) {
                set_vec3(var15, 0.0, 1.0, 0.0);
            } else {
                set_vec3(var15, 0.0, 0.0, 1.0);
            }
        }
    }
    add_vectors(var6, var15, 3, var5);
    double var16[3];
    if (input[0] <= 90.29013442993164) {
        if (input[0] <= 88.99232864379883) {
            set_vec3(var16, 0.0, 0.0, 1.0);
        } else {
            if (input[3] <= 30.2672700881958) {
                set_vec3(var16, 0.0, 1.0, 0.0);
            } else {
                set_vec3(var16, 0.0, 0.0, 1.0);
            }
        }
    } else {
        if (input[2] <= 22.15372085571289) {
            if (input[3] <= 40.43387031555176) {
                set_vec3(var16, 1.0, 0.0, 0.0);
            } else {
                set_vec3(var16, 0.0, 0.0, 1.0);
            }
        } else {
            if (input[3] <= 31.789849281311035) {
                set_vec3(var16, 0.0, 1.0, 0.0);
            } else {
                set_vec3(var16, 0.0, 0.0, 1.0);
            }
        }
    }
    add_vectors(var5, var16, 3, var4);
    double var17[3];
    if (input[0] <= 90.6403923034668) {
        if (input[3] <= 9.415399551391602) {
            if (input[0] <= 87.0) {
                set_vec3(var17, 0.0, 0.0, 1.0);
            } else {
                set_vec3(var17, 0.0, 1.0, 0.0);
            }
        } else {
            if (input[2] <= 61.623783111572266) {
                if (input[2] <= 60.9774112701416) {
                    if (input[3] <= 31.647231101989746) {
                        if (input[1] <= 111.3760986328125) {
                            set_vec3(var17, 0.0, 1.0, 0.0);
                        } else {
                            set_vec3(var17, 0.0, 0.0, 1.0);
                        }
                    } else {
                        set_vec3(var17, 0.0, 0.0, 1.0);
                    }
                } else {
                    set_vec3(var17, 0.0, 1.0, 0.0);
                }
            } else {
                if (input[0] <= 89.41382217407227) {
                    set_vec3(var17, 0.0, 0.0, 1.0);
                } else {
                    if (input[3] <= 40.624691009521484) {
                        set_vec3(var17, 0.0, 1.0, 0.0);
                    } else {
                        set_vec3(var17, 0.0, 0.0, 1.0);
                    }
                }
            }
        }
    } else {
        if (input[0] <= 96.17595672607422) {
            if (input[3] <= 37.8552885055542) {
                if (input[2] <= 20.047212600708008) {
                    set_vec3(var17, 1.0, 0.0, 0.0);
                } else {
                    set_vec3(var17, 0.0, 1.0, 0.0);
                }
            } else {
                set_vec3(var17, 0.0, 0.0, 1.0);
            }
        } else {
            if (input[2] <= 26.221489906311035) {
                set_vec3(var17, 1.0, 0.0, 0.0);
            } else {
                set_vec3(var17, 0.0, 1.0, 0.0);
            }
        }
    }
    add_vectors(var4, var17, 3, var3);
    double var18[3];
    if (input[0] <= 89.91395950317383) {
        if (input[2] <= 71.30355834960938) {
            if (input[3] <= 14.253886699676514) {
                if (input[1] <= 119.79433822631836) {
                    if (input[3] <= 5.939317464828491) {
                        if (input[2] <= 68.88050079345703) {
                            set_vec3(var18, 0.0, 1.0, 0.0);
                        } else {
                            set_vec3(var18, 0.0, 0.0, 1.0);
                        }
                    } else {
                        set_vec3(var18, 0.0, 1.0, 0.0);
                    }
                } else {
                    if (input[0] <= 85.92390823364258) {
                        set_vec3(var18, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var18, 0.0, 1.0, 0.0);
                    }
                }
            } else {
                if (input[3] <= 23.4641752243042) {
                    if (input[3] <= 20.97260284423828) {
                        set_vec3(var18, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var18, 0.0, 1.0, 0.0);
                    }
                } else {
                    set_vec3(var18, 0.0, 0.0, 1.0);
                }
            }
        } else {
            if (input[3] <= 11.520169734954834) {
                if (input[1] <= 130.6210479736328) {
                    if (input[3] <= 10.588211059570312) {
                        if (input[0] <= 87.0) {
                            set_vec3(var18, 0.0, 0.0, 1.0);
                        } else {
                            set_vec3(var18, 0.0, 1.0, 0.0);
                        }
                    } else {
                        set_vec3(var18, 0.0, 1.0, 0.0);
                    }
                } else {
                    if (input[2] <= 83.05875396728516) {
                        if (input[0] <= 86.66640853881836) {
                            set_vec3(var18, 0.0, 0.0, 1.0);
                        } else {
                            set_vec3(var18, 0.0, 1.0, 0.0);
                        }
                    } else {
                        set_vec3(var18, 0.0, 0.0, 1.0);
                    }
                }
            } else {
                set_vec3(var18, 0.0, 0.0, 1.0);
            }
        }
    } else {
        if (input[2] <= 22.15372085571289) {
            if (input[3] <= 38.55550956726074) {
                set_vec3(var18, 1.0, 0.0, 0.0);
            } else {
                set_vec3(var18, 0.0, 0.0, 1.0);
            }
        } else {
            if (input[3] <= 32.269317626953125) {
                set_vec3(var18, 0.0, 1.0, 0.0);
            } else {
                set_vec3(var18, 0.0, 0.0, 1.0);
            }
        }
    }
    add_vectors(var3, var18, 3, var2);
    double var19[3];
    if (input[3] <= 15.375060081481934) {
        if (input[1] <= 93.85237503051758) {
            if (input[2] <= 26.769408226013184) {
                set_vec3(var19, 1.0, 0.0, 0.0);
            } else {
                if (input[0] <= 86.98477554321289) {
                    set_vec3(var19, 0.0, 0.0, 1.0);
                } else {
                    set_vec3(var19, 0.0, 1.0, 0.0);
                }
            }
        } else {
            if (input[2] <= 18.768545627593994) {
                set_vec3(var19, 1.0, 0.0, 0.0);
            } else {
                if (input[1] <= 135.444091796875) {
                    if (input[3] <= 8.787459373474121) {
                        if (input[0] <= 87.0) {
                            set_vec3(var19, 0.0, 0.0, 1.0);
                        } else {
                            set_vec3(var19, 0.0, 1.0, 0.0);
                        }
                    } else {
                        if (input[3] <= 8.873868942260742) {
                            set_vec3(var19, 0.0, 0.0, 1.0);
                        } else {
                            set_vec3(var19, 0.0, 0.8643410852713178, 0.13565891472868216);
                        }
                    }
                } else {
                    if (input[0] <= 87.0) {
                        set_vec3(var19, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var19, 0.0, 1.0, 0.0);
                    }
                }
            }
        }
    } else {
        if (input[3] <= 18.939433097839355) {
            if (input[0] <= 87.14458465576172) {
                set_vec3(var19, 0.0, 0.0, 1.0);
            } else {
                set_vec3(var19, 0.0, 1.0, 0.0);
            }
        } else {
            if (input[0] <= 93.46842193603516) {
                if (input[0] <= 88.99232864379883) {
                    set_vec3(var19, 0.0, 0.0, 1.0);
                } else {
                    if (input[0] <= 89.01523971557617) {
                        set_vec3(var19, 0.0, 1.0, 0.0);
                    } else {
                        set_vec3(var19, 0.0, 0.0, 1.0);
                    }
                }
            } else {
                set_vec3(var19, 0.0, 1.0, 0.0);
            }
        }
    }
    add_vectors(var2, var19, 3, var1);
    mul_vector_number(var1, 0.1, 3, var0);
    output[0] = var0[0]; output[1] = var0[1]; output[2] = var0[2];
}


#endif // DROWNT_MODEL_4F_H
