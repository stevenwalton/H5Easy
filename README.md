# H5Easy
---------
Simple implementations of HDF5 Reading and Writing

The purpose of this is to provide an easier method to read and write from hdf5 formats. Currently the program works with only 
I32LE integers and IEEE F32BE floats. The program will auto detect if you are trying to read or write in integer or float and
properly store the data as such. With just a few lines you can read or write data easily. 

## How to use
-------------
The classes here are simple to use and reduce your reading and writing of h5 files to just a few lines. The intention was to mimic the behaviour 
of Python's h5py. With just a few lines you can quickly grab or write to h5 files. 

To compile just make sure that you have `h5rw.h` in your `LD_LIBRARY_PATH`. If you are on linux run `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/h5rwDir` 
or just place it in `/usr/include`. To compile you MUST use an h5 compiler, such as `h5c++`. 

If a user wants to write to a h5 file all they need to do is run the following
```
WriteH5 data;
data.setFileName("myH5File.h5");
data.setVarName("myVariableName");
data.writeData(myVectoredData);
// For groups
data.createGroup("/my/group/name");
data.setVarName("/my/group/name/myVariableName");
```
The libraries do not care if you pass it a float or an int vector, just that you pass it a vector. It will write in the proper method.

If a user wants to read the data from the h5 file
```
LoadH5 data;
data.setFileName("myH5File.h5");
data.setVarName("myVariableName");
vector<int/float> loadedData = data.getData();
// For groups
data.setVarName("/my/group/name/myVariableName");
vector<int/float> loadedData = data.getData();
```

I have included a test file so that you can ensure that things are working properly.
Note that this method also works for loading in group data. All you have to do is type the full path as the variable name.

### Assumptions
---------------
- You are using vectors (if you aren't, you should for reasons other than using these files)
- You are using 1D vectors (reading and writing)
- You want a I32LE (long int 32) storage for your integers (reading and writing)
- You want a IEEE 32 Float. (reading and writing)

### ISSUES
-----------
###### Libraries not linking:
 - Make sure hdf5-dev is installed. 
 - Check that the libraries are being linked properly. They should be located in `/usr/include` but if you can't find them then run `sudo find /usr -name hdf5` or `sudo find /usr -name H5Cpp.h`. 
   Test that this is the issue by running `h5c++ -I/path/that/you/found test.cpp -o test` If this works then add it to your LD_LIBRARY_PATH. `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/that/you/found`. Add that to your `.bashrc` or shell's rc file. 
###### h5dump not working
 - Make sure that hdf5-tools is installed
If you can not find these through your package manager just search for `hdf5`


### Dependencies
----------------
- h5 libraries and its dependencies (if you use python and have Anaconda installed these will be sufficient)

### Problems / Feature Requests
--------------
Please open an issue on the GitHub page for bugs in the code or feature requests. I will try to address everything as best as I can

### TODO
--------
Features I plan on adding
- Determining different int or float types when reading (aka someone who isn't using I32LE or IEEE F32BE)
- Multidimensional arrays
