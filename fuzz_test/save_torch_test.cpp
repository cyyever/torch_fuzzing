/*!
 * \file load_torch_test.cpp
 *
 */

#include <sstream>
#include <torch/csrc/api/include/torch/serialize.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  try {
    if (Size <= 1) {
      return 0;
    }

    std::vector<torch::ScalarType> dtypes{torch::kU8,  torch::kI8,  torch::kI16,
                                          torch::kI32, torch::kI64, torch::kF16,
                                          torch::kF32};
    auto data = torch::empty({static_cast<long>(Size - 1)},
                             dtypes[Data[0] % dtypes.size()]);
    memcpy(data.data_ptr<uint8_t>(), Data + 1, Size - 1);
    torch::save(data, "/tmp/__save_torch_test");

  } catch (...) {
  }
  return 0; // Non-zero return values are reserved for future use.
}
