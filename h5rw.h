/*
 * Class functions for an easier h5 read and write method.
 * Created by: Steven Walton
 * Email: walton.stevenj@gmail.com
 */
#ifndef H5RW_H
#define H5RW_H

#include <iostream>
#include <vector>
#include <string>

#include "H5Cpp.h"

using namespace H5;

class WriteH5
{
   private:
   public:
      std::string variable;
      std::string filename;
      // sets our filename and our variable name
      void setFileName(std::string name) {filename = name;};
      void setVarName(std::string name) {variable = name;};
      // Functions to be overloaded
      void writeData(std::vector<int>);
      void writeData(std::vector<float>);
};

class LoadH5
{
   private:
   public:
      std::string variable;
      std::string filename;
      // sets our filename and our variable name
      void setFileName(std::string name) {filename = name;};
      void setVarName(std::string name) {variable = name;};
      // Read functions
      std::vector<int> getDataint() const;
      std::vector<float> getDatafloat() const;
      // We now make a proxy class so that we can overload the return type and use a single
      // function to get data whether int or float. This could be made more advanced by 
      // adding more data types (such as double). 
      class Proxy
      {
         private:
            LoadH5 const* myOwner;
         public:
            Proxy( const LoadH5* owner ) : myOwner( owner ) {}
            operator std::vector<int>() const
            {
               return myOwner->getDataint();
            }
            operator std::vector<float>() const
            {
               return myOwner->getDatafloat();
            }
      };
      // Here we use the Proxy class to have a single getData function
      Proxy getData() const {return Proxy(this);}
};


#endif
/*
 * Source file for the easy implementation of h5 read and writing
 * Created by: Steven Walton
 * Email: walton.stevenj@gmail.com
 */
//#include "h5rw.h"

/*
 * ************************************************************************************************
 * ************************************ Write Functions *******************************************
 * ************************************************************************************************
 */
// Integer implementation of our write data function
void WriteH5::writeData(std::vector<int> data)
{
   Exception::dontPrint();

   uint itr = 0; // Used to ensure we don't get stuck in an infinite loop
   uint npts = data.size(); // size of our data
   int *a = new int[npts]; // convert to an array
   int vrank = 1; // since we are using std::vectors we are storing everything in one dimension
   // convert std::vector to array. H5 does not seem to like the pointer implementation
   for (size_t i = 0; i < npts; i++)
      a[i] = data[i];
   // conventional syntax for H5 data writing
   hsize_t dims[1];
   dims[0] = npts;
   // Let's make sure we are doing what we want and output it to the std output
   std::cout << "We have WriteH5::filename: " << WriteH5::filename << std::endl;
   std::cout << "data: " << WriteH5::variable << std::endl;

   // We need to set these parameters for the H5 data file writing
   const H5std_string FILE_NAME(WriteH5::filename);
   H5std_string DATASET_NAME(WriteH5::variable);
   // loop here will check if the file exists. 
   while (true)
   {
      // This assumes that the file already exists and will then write to the file
      try
      {
         H5File file(FILE_NAME, H5F_ACC_RDWR);
         DataSpace dsp = DataSpace(vrank,dims);
         DataSet dset = file.createDataSet(DATASET_NAME, PredType::STD_I32LE, dsp);
         dset.write(a, PredType::STD_I32LE);

         // remember to close everything and delete our arrays
         dset.close();
         dsp.close();
         file.close();
         delete[] a;
         break;
      }
      // Here we are catching if the file does not exist. We will then create a new file and return
      // back to the try statement
      catch (FileIException error)
      {
         H5File file(FILE_NAME, H5F_ACC_TRUNC);
         file.close();
         // Just some warning that we have gone through this catch
         std::cout << "i-itr: " << itr << std::endl;
         itr++;
         // This is to prevent us from getting caught in an infinite loop. While (true) loops
         // are useful, but they can be dangerous. Always ensure some escape sequence. Could
         // just use a for loop
         if ( itr > 3) 
         {
            std::cout << "We've tried too many times in the Int writing sequence" << std::endl;
            break;
         }
      }
   }
}


// Almost exact copy of the integer implementation but overloaded with floats
void WriteH5::writeData(std::vector<float> data)
{
   Exception::dontPrint();

   uint itr = 0;
   uint npts = data.size();
   float*a = new float[npts];
   int vrank = 1;
   for (size_t i = 0; i < npts; i++)
      a[i] = data[i];
   hsize_t dims[1];
   dims[0] = npts;
   std::cout << "We have WriteH5::filename: " << WriteH5::filename << std::endl;
   std::cout << "data: " << WriteH5::variable << std::endl;

   const H5std_string FILE_NAME(WriteH5::filename);
   H5std_string DATASET_NAME(WriteH5::variable);
   while (true)
   {
      try
      {

         H5File file(FILE_NAME, H5F_ACC_RDWR);
         
         DataSpace dsp = DataSpace(vrank,dims);
         DataSet dset = file.createDataSet(DATASET_NAME, PredType::IEEE_F32BE, dsp);
         dset.write(a, PredType::IEEE_F32BE);
         std::cout << "Data written" << std::endl;

         dset.close();
         dsp.close();
         file.close();
         delete[] a;
         break;
      }
      catch (FileIException error)
      {
         H5File file(FILE_NAME,H5F_ACC_TRUNC);
         file.close();
         itr++;
         std::cout << "f-itr: " << itr << std::endl;
         if (itr > 3)
         {
            std::cout << "We've tried too many times in the float writing sequence" << std::endl;
            break;
         }
      }
   }
}

/*
 * ************************************************************************************************
 * ************************************ Read Functions ********************************************
 * ************************************************************************************************
 */

// Our int loading function
std::vector<int> LoadH5::getDataint() const
{
   try
   {
      Exception::dontPrint();
      std::cout << "Getting int data" << std::endl;
      H5std_string FILE_NAME(LoadH5::filename);
      H5File file(FILE_NAME, H5F_ACC_RDONLY); // Only reads
      DataSet dataset = file.openDataSet(LoadH5::variable);
      DataType datatype = dataset.getDataType();
      DataSpace dataspace = dataset.getSpace();
      const int npts = dataspace.getSimpleExtentNpoints(); // Gets length of data
      H5T_class_t classt = datatype.getClass(); // Gets the data type of the data
      // Let's make a quick error check
      if ( classt != 0 )
      {
         std::cout << "This is not an int... you can't save this as an int." << std::endl;
      }
      int *data = new int[npts]; // allocate at run time what the size will be
      dataset.read(data, PredType::STD_I32LE); // Our standard integer
      std::vector<int> v(data, data + npts); // Arrays are nice, but vectors are better
      // Manage our memory properly
      delete[] data;
      dataspace.close();
      datatype.close();
      dataset.close();
      file.close();
      return v;
   }
   catch (FileIException error)
   {
      error.printError();
      std::vector<int> err;
      return err;
   }
   catch (GroupIException error)
   {
      error.printError();
      std::vector<int> err;
      return err;
   }
}

// Same as our int function, but with float. Uses IEEE_F32BE
std::vector<float> LoadH5::getDatafloat() const
{
   try
   {
      Exception::dontPrint();
      std::cout << "Getting float data" << std::endl;
      H5std_string FILE_NAME(LoadH5::filename);
      H5File file(FILE_NAME, H5F_ACC_RDONLY);
      DataSet dataset = file.openDataSet(LoadH5::variable);
      DataType datatype = dataset.getDataType();
      DataSpace dataspace = dataset.getSpace();
      const int npts = dataspace.getSimpleExtentNpoints();
      H5T_class_t classt = datatype.getClass();
      if ( classt != 1 )
      {
         std::cout << "This is not a float... you can't save this as a float." << std::endl;
      }
      float *data = new float[npts];
      dataset.read(data, PredType::IEEE_F32BE);
      std::vector<float> v(data, data + npts);
      delete[] data;
      dataspace.close();
      datatype.close();
      dataset.close();
      file.close();
      return v;
   }
   catch (FileIException error)
   {
      error.printError();
      std::vector<float> err;
      return err;
   }
   catch (GroupIException error)
   {
      error.printError();
      std::vector<float> err;
      return err;
   }
}
