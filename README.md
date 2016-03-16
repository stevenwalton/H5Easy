# H5Easy
---------
Simple implementations of HDF5 Reading and Writing

## How to use
-------------
The classes here are simple to use and reduce your reading and writing of h5 files to just a few lines. The intention was to mimic the behaviour 
of Python's h5py. With just a few lines you can quickly grab or write to h5 files. 

If a user wants to write to a h5 file all they need to do is run the following
```
WriteH5 data;
data.setFileName("myH5File.h5");
data.setVarName("myVariableName");
data.writeData(myVectoredData);
```
The libraries do not care if you pass it a float or an int vector, just that you pass it a vector. It will write in the proper method.

If a user wants to read the data from the h5 file
```
LoadH5 data;
data.setFileName("myH5File.h5");
data.setVarName("myVariableName");
vector<int/float> loadedData = data.getData();
```

I have included a test file so that you can ensure that things are working properly

### Assumptions
---------------
- You are using vectors (if you aren't, you should for reasons other than using these files)
- You want a I32LE (long int 32) storage for your integers (reading and writing)
- You want a IEEE 32 Float. (reading and writing)

### Problems / Feature Requests
--------------
Please open an issue on the GitHub page for bugs in the code or feature requests. I will try to address everything as best as I can

### TODO
--------
Features I plan on adding
- Groups
- Determining different int or float types when reading (aka someone who isn't using this and is using weird data)
