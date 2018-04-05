/**
Software License Agreement (BSD)

\file      json_transport.hpp
\authors   Paul Bovbel <pbovbel@locusrobotics.com>
\copyright Copyright (c) (2018,), Locus Robotics, All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted
provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions
and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or other materials provided with
the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to
endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/
#include "nlohmann/json.hpp"
#include "json_msgs/Json.h"

#include <ros/message_traits.h>
#include <ros/serialization.h>

ROS_STATIC_ASSERT(sizeof(nlohmann::json) == 16);

namespace ros
{
namespace message_traits
{

typedef nlohmann::json json_t;
typedef json_msgs::Json json_msg_t;

template<>
struct MD5Sum<json_t>
{
  static const char* value()
  {
    // Ensure that if the definition of json_msg_t changes we have a compile error here.
    ROS_STATIC_ASSERT(MD5Sum<json_msg_t>::static_value1 == 0xc55cc30de2de2e48ULL);
    ROS_STATIC_ASSERT(MD5Sum<json_msg_t>::static_value2 == 0x3336fe2549c9f941ULL);
    return MD5Sum<json_msg_t>::value();
  }

  static const char* value(const json_t&)
  {
    return value();
  }
};

template<>
struct DataType<json_t>
{
  static const char* value()
  {
    return DataType<json_msg_t>::value();
  }

  static const char* value(const json_t&)
  {
    return value();
  }
};

template<>
struct Definition<json_t>
{
  static const char* value()
  {
    return Definition<json_msg_t>::value();
  }

  static const char* value(const json_t&)
  {
    return value();
  }
};
} // namespace message_traits

namespace serialization
{

template<>
struct Serializer<json_t>
{
  template<typename Stream>
  inline static void write(Stream& stream, const json_t& json)
  {
    stream.next(json.dump());
  }

  template<typename Stream>
  inline static void read(Stream& stream, json_t& json)
  {
    std::string data;
    stream.next(data);
    json = json_t::parse(data);
  }

  inline static uint32_t serializedLength(const json_t& json)
  {
    return json.dump().size() + 4;
  }
};

} // namespace serialization
} // namespace ros
