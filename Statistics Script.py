import pandas as pd
import numpy as np
import scipy
import scipy.stats as st
import os
import math
import csv

row = []

'''
for x in os.walk('.'):
    for i in ['2s', '4s', '5s']:
        if './Interarrival_' + i == str(x[0]):
            for y in os.walk(x[0]):
                for v in ['2', '4', '5', '6']:
                    if './Interarrival_'+ i +'/I'+ i[0] +'_V' + v == str(y[0]):
                        for root, dirs, files in os.walk(y[0]):
                            for name in files:
                                if(str(name)=='GLF.csv'):
                                    df = pd.read_csv('./Interarrival_'+ i +'/I'+ i[0] +'_V' + v + '/GLF.csv')
                                    # mean = float(df['mean'].mean())
                                    row.append(['I'+ i[0] +'_V' + v, float(df['mean'].mean().round(2))])

with open('./medie.csv', 'w') as file:
    w = csv.writer(file)
    w.writerow(row)



for x in os.walk('.'):
    for i in ['1s', '2s', '4s', '5s']:
        if './Interarrival_' + i == str(x[0]):
            for y in os.walk(x[0]):
                for v in ['2', '4', '5', '6']:
                    row = []
                    if './Interarrival_'+ i +'/I'+ i[0] +'_V' + v == str(y[0]):
                        for root, dirs, files in os.walk(y[0]):
                            for name in files:
                                if(str(name)=='GLF.csv'):
                                    df = pd.read_csv('./Interarrival_'+ i +'/I'+ i[0] +'_V' + v + '/GLF.csv')
                                    data = ["0."+ v +"s", df['mean'].mean().round(2)]
                                    row.append(data)
                                if(str(name)=='RLF.csv'):
                                    df2 = pd.read_csv('./Interarrival_'+ i +'/I'+ i[0] +'_V' + v + '/RLF.csv')
                                    data2 = ["0."+ v +"s", df2['mean'].mean().round(2)]
                                    row.append(data2)
                        with open('./Interarrival_' + i+'/Vacation_0.'+ v +'s.csv', 'w') as file:
                            w = csv.writer(file)
                            w.writerow(row)
'''

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
                                # if(str(name)=='GLF.csv'):
                                #     df = pd.read_csv('./Interarrival_'+ i +'/I'+ i[0] +'_V' + v + '/GLF.csv')
                                #     mean = df['mean'].mean()
                                #     print("Interarrival "+ i +" and 0."+ v +"s Vacation")
                                #     print("Mean: "+ str(mean))
                                #     stddev = df['mean'].std()
                                #     print("StdDev: " + str(stddev))
                                #     variance = df['mean'].var()
                                #     print("Var: " + str(variance))
                                #     stdErrAvg = stddev/(math.sqrt(runs))
                                #     print("StdErr: " + str(stdErrAvg))
                                #     min_95 = mean - (t95 * math.sqrt(variance)/math.sqrt(runs))
                                #     max_95 = mean + (t95 * math.sqrt(variance)/math.sqrt(runs))
                                #     print("LowBound t95 ConfInt: " + str(min_95) + " - UpBound ConfInt: " + str(max_95))
                                #     min_90 = mean - (t90 * math.sqrt(variance)/math.sqrt(runs))
                                #     max_90 = mean + (t90 * math.sqrt(variance)/math.sqrt(runs))
                                #     print("LowBound t90 ConfInt: " + str(min_90) + " - UpBound ConfInt: " + str(max_90) + "\n")
                                #     row.append(["0."+ v +"s", round(mean,3), round(min_95,3), round(max_95,3)])
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