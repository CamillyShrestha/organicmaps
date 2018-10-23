#pragma once

#include "platform/measurement_utils.hpp"

#include <cstdint>
#include <limits>
#include <string>

namespace generator
{
uint16_t constexpr kNoneMaxSpeed = std::numeric_limits<uint16_t>::max();

/// \brief Obtains |speed| and |units| by road category based on
/// the table in https://wiki.openstreetmap.org/wiki/Speed_limits
/// This method should be updated regularly. Last update: 23.10.18.
/// \returns true if |speed| and |units| is found for |category| and these fields are filled
/// and false otherwise.
/// \note For example by passing string "RU:urban", you'll get
/// speed = 60 and units = Units::Metric.
/// \note If the method returns true the field |speed| may be filled with |kNoneMaxSpeed| value.
/// It means no speed limits for the |category|. It's currently actual for Germany.
bool RoadCategoryToSpeed(std::string const & category, uint16_t & speed,
                         measurement_utils::Units & units);
}  // generator
