#pragma once

#include "log.hpp"
#include "output.hpp"

#include <vector>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>

namespace cujak {
namespace util {

/**
 * I/O for one-dimensional data
 */
namespace io {

template <typename T> class ASCII;
template <typename T> class BINARY;

/** load data from file
 * \tparam T typename of data (double, float, int)
 * \tparam Format ASCII or BINARY
 *
 * \return size of data
 * \param filename in which data is saved
 * \param data loaded data will be placed here
 */
template <typename T, template <class> class Format = ASCII>
int load(std::string filename, T *data) {
  return Format<T>::load(filename, data);
}

/** load data from file
 * \tparam T typename of data (double, float, int)
 * \tparam Format ASCII or BINARY
 *
 * \return size of data
 * \param filename in which data is saved
 * \param data loaded data will be placed here
 */
template <typename T, template <class> class Format = ASCII>
void load(std::string filename, int N, T *data) {
  Format<T>::load(filename, N, data);
}

/** load data from file
 * \tparam T typename of data (double, float, int)
 * \tparam Format ASCII or BINARY
 *
 * \return vector containing data
 * \param filename in which data is saved
 */
template <typename T, template <class> class Format = ASCII>
std::vector<T> load(std::string filename) {
  return Format<T>::load(filename);
}

/** dump data into file
 * \tparam T typename of data (double, float, int)
 * \tparam Format ASCII or BINARY
 *
 * \param filename in which data will be saved
 * \param N size of data
 * \param data to be saved
 */
template <typename T, template <class> class Format = ASCII>
void dump(std::string filename, int N, T *data) {
  Format<T>::dump(filename, N, data);
}

/*
 * implementations
 * 上述の関数を部分特殊化できないので(C++の制限)、
 * クラスに分けて特殊化する
 */

/**
 * \class ASCII io.hpp "utility/io.hpp"
 *
 * I/O for ascii format
 */
template <typename T> class ASCII {
  static int precision();

public:
  static void load(std::string filename, int N, T *data);
  static int load(std::string filename, T *data);
  static std::vector<T> load(std::string filename);
  static void dump(std::string filename, int N, T *data);
};

template <> int ASCII<float>::precision() { return 8; }
template <> int ASCII<double>::precision() { return 15; }

template <typename T> std::vector<T> ASCII<T>::load(std::string filename) {
  std::ifstream ifs(filename);
  if (ifs.fail()) {
    char msg[128];
    sprintf(msg, "file %s does not found", filename.c_str());
    throw std::runtime_error(msg);
  }

  std::vector<T> data;
  std::string line;
  while (std::getline(ifs, line)) {
    T val;
    try {
      val = boost::lexical_cast<T>(line);
    }
    catch (...) {
      char msg[128];
      sprintf(msg, "cannot convert: '%s'", line.c_str());
      log(msg, std::cerr);
      continue;
    }
    data.push_back(val);
  }
  return data;
}

template <typename T> int ASCII<T>::load(std::string filename, T *data) {
  std::vector<T> data_ = ASCII<T>::load(filename);
  std::copy(data_.begin(), data_.end(), data);
  return data_.size();
}

template <typename T>
void ASCII<T>::load(std::string filename, int N, T *data) {
  std::vector<T> data_ = ASCII<T>::load(filename);
  if ((int)data_.size() == N) {
    std::copy(data_.begin(), data_.end(), data);
  } else if ((int)data_.size() > N) {
    log("Strip surplus data", std::cerr);
    std::copy(data_.begin(), data_.begin() + N, data);
  } else {
    char msg[128];
    sprintf(msg, "Cannot enough data from file '%s'", filename);
    throw std::runtime_error(msg);
  }
}

template <typename T>
void ASCII<T>::dump(std::string filename, int N, T *data) {
  std::ofstream ofs(filename);
  if (ofs.fail()) {
    char msg[128];
    sprintf(msg, "file %s cannot be opened", filename.c_str());
    throw std::runtime_error(msg);
  }
  ofs << std::scientific << std::setprecision(ASCII<T>::precision());
  for (int i = 0; i < N; ++i) {
    ofs << data[i] << '\n';
  }
  ofs << std::flush;
}

/**
 * \class BINARY io.hpp "utility/io.hpp"
 *
 * I/O for binary format
 */
template <typename T> class BINARY {
public:
  static int load(std::string filename, T *data);
  static std::vector<T> load(std::string filename);
  static void dump(std::string filename, int N, T *data);
};
} // namespace io
} // namespace util
} // namespace cujak
