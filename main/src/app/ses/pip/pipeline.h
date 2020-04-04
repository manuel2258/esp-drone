#ifndef DRONE_SRC_APP_SES_PIP_PIPELINE
#define DRONE_SRC_APP_SES_PIP_PIPELINE

#include <memory>
#include <vector>

#include "pipeline_types.h"

namespace pip {

/**
 * @brief Processes a InputPkg into direct motor values.
 * Uses a series of proccessors to change input / output values.
 */
class Pipeline {
private:
  std::vector<IInputProcessor *> *inputs;
  IConverter *converter;
  std::vector<IOutputProcessor *> *outputs;

  Output *process(Input &in);

public:
  Pipeline(std::vector<IInputProcessor *> *in, IConverter *conv,
           std::vector<IOutputProcessor *> *out);

  ~Pipeline();

  std::unique_ptr<Output> process_input(pkg::InputPkg &pkg);
};

class PipelineBuilder {
private:
  std::vector<IInputProcessor *> *inputs;
  IConverter *converter;
  std::vector<IOutputProcessor *> *outputs;

public:
  PipelineBuilder();

  std::unique_ptr<Pipeline> build();

  PipelineBuilder &add_input_processor(IInputProcessor *in);

  PipelineBuilder &add_output_processor(IOutputProcessor *out);

  PipelineBuilder &set_converter(IConverter *conv);
};

} // namespace pip
