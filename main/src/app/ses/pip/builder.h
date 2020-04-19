#ifndef DRONE_SRC_APP_SES_PIP_BUILDER
#define DRONE_SRC_APP_SES_PIP_BUILDER

#include <memory>
#include <vector>

#include "pipeline.h"
#include "pipeline_types.h"

namespace pip {

class PipelineBuilder {
private:
  std::vector<IInputProcessor *> *inputs = nullptr;
  IConverter *converter = nullptr;
  std::vector<IOutputProcessor *> *outputs = nullptr;

public:
  PipelineBuilder();
  ~PipelineBuilder();

  std::unique_ptr<Pipeline> build();

  /**
   * @brief Adds ptr as input processor
   */
  PipelineBuilder &add_input_processor(IInputProcessor *in);

  /**
   * @brief Adds ptr as output processor
   */
  PipelineBuilder &add_output_processor(IOutputProcessor *out);

  /**
   * @brief Sets ptr as converter
   */
  PipelineBuilder &set_converter(IConverter *conv);
};
} // namespace pip

#endif