import pandas as pd
import numpy as np
import scipy
import scipy.stats as st
import os
import math
import csv

row = []
t95 = 2.093
t90 = 1.729
runs = 20

for x in os.walk('.'):
    for i in ['1s', '2s', '4s', '5s']:
        if './Interarrival_' + i == str(x[0]):
            for y in os.walk(x[0]):
                for v in ['2', '4', '5', '6']:
                    row = []
                    if './Interarrival_'+ i +'/I'+ i[0] +'_V' + v == str(y[0]):
                        for root, dirs, files in os.walk(y[0]):
                            for name in files:
                                if(str(name)=='RLF.csv'):
                                    df2 = pd.read_csv('./Interarrival_'+ i +'/I'+ i[0] +'_V' + v + '/RLF.csv')
                                    mean2 = df2['mean'].mean()
                                    print("Interarrival "+ i +" and 0."+ v +"s Vacation")
                                    print("Mean: "+ str(mean2))
                                    stddev2 = df2['mean'].std()
                                    print("StdDev: " + str(stddev2))
                                    variance2 = df2['mean'].var()
                                    print("Var: " + str(variance2))
                                    stdErrAvg2 = stddev2/(math.sqrt(runs))
                                    print("StdErr: " + str(stdErrAvg2))
                                    min2_95 = mean2 - (t95 * math.sqrt(variance2)/math.sqrt(runs))
                                    max2_95 = mean2 + (t95 * math.sqrt(variance2)/math.sqrt(runs))
                                    print("LowBound t95 ConfInt: " + str(min2_95) + " - UpBound ConfInt: " + str(max2_95))
                                    min2_90 = mean2 - (t90 * math.sqrt(variance2)/math.sqrt(runs))
                                    max2_90 = mean2 + (t90 * math.sqrt(variance2)/math.sqrt(runs))
                                    print("LowBound t90 ConfInt: " + str(min2_90) + " - UpBound ConfInt: " + str(max2_90) + "\n")
                                    row.append(["0."+ v +"s", round(mean2,3), round(min2_95, 3), round(max2_95, 3)])
                        with open('./Interarrival_' + i+'/Vacation_0.'+ v +'s.csv', 'w') as file:
                            w = csv.writer(file)
                            w.writerow(row)
