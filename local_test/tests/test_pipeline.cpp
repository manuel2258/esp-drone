#include "app/ses/pip/builder.h"
#include "app/ses/pip/pipeline.h"
#include "app/ses/pip/pipeline_types.h"
#include "app/ses/pip/processors.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(pipeline_suite)

BOOST_AUTO_TEST_CASE(builder_minimal) {
  pip::PipelineBuilder builder;
  auto converter = new pip::CurveConverter();

  pip::Input input;

  auto pipeline = builder.set_converter(converter).build();

  auto output = pipeline->process(input);

  BOOST_CHECK_NE(nullptr, output);

  delete output;
}

BOOST_AUTO_TEST_SUITE_END()