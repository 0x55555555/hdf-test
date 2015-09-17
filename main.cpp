#include "H5Cpp.h"
#include <iostream>

const std::size_t data_length = 3000;
int data[data_length] = { 0 };

int main(int argc, char **argv) {
  std::cout << "Running Test" << std::endl;
  
  std::size_t idx = 0;
  while (true) {
    std::cout << "File " << idx << std::endl;
    H5::H5File file("test" + std::to_string(idx) + ".h5", H5F_ACC_TRUNC);
    ++idx;
  
    // Create the data space for the dataset.
    hsize_t dims[1] = { 0 };
    hsize_t maxdims[1] = { H5S_UNLIMITED };
    H5::DataSpace dataspace(1, dims, maxdims);
  
    hsize_t chunkdims[1] = { data_length };
    H5::DSetCreatPropList prop;
    prop.setChunk(1, chunkdims);
  
    // Create the dataset.
    file.createDataSet("test", H5::PredType::NATIVE_INT, dataspace, prop);
  
    auto extend = [&](int *data, hsize_t length) {
      auto dataset = file.openDataSet("test");
    
      hsize_t existing_size = 0;
      H5::DataSpace filespace(dataset.getSpace());
      filespace.getSimpleExtentDims(&existing_size);
    
      hsize_t new_size = existing_size + length;
      dataset.extend(&new_size);
    
      hsize_t offset = existing_size;
      hsize_t size = length;
      filespace = dataset.getSpace();
      filespace.selectHyperslab(H5S_SELECT_SET, &size, &offset);
  
      H5::DataSpace memspace(1, &length, NULL);
      dataset.write(data, H5::PredType::NATIVE_INT, memspace, filespace);
    };
  
    for (std::size_t i = 0; i < 100; ++i) {
      extend(data, data_length);
    }
  }
  
  return 0;
}
