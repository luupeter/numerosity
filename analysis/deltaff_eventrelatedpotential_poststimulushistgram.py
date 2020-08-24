
#%%
#import csv
import numpy as np
#from pathlib import Path


#%%
events = 20 #number of timepoint per stimulus cycle
dfpercentile = 8 #take the bottom percentile of the image intensity to use as ΔF/F from baseline

#%%
mydata = np.genfromtxt("C:/Users/Peter/Desktop/Values.csv", delimiter=',')
print(mydata.dtype)
print(mydata.shape)

atrace=mydata[:,1]
# convert to ΔF/F from baseline percentile (cite UPENN fluorosnapp if people quesiton methods)
baseline = np.percentile(atrace, dfpercentile)
atrace = (atrace - baseline)/baseline

# reshape the data into and array where rows are number of rounds and columns are timepoint
if atrace.size % events != 0: # remove excess frames
    atrace = atrace[0:atrace.size-(atrace.size % events):1]
    
atrace = atrace.reshape(int(atrace.size/events), events)

# %%

np.savetxt("foo.csv", atrace, delimiter=",")


# %%
