# Software License Agreement (BSD)
#
# \file      json_transport.py
# \authors   Paul Bovbel <pbovbel@locusrobotics.com>
# \copyright Copyright (c) (2018,), Locus Robotics, All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification, are permitted
# provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this list of conditions
# and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice, this list of
# conditions and the following disclaimer in the documentation and/or other materials provided with
# the distribution.
# 3. Neither the name of the copyright holder nor the names of its contributors may be used to
# endorse or promote products derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
# FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
# IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
# OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
import msgpack

from json_msgs import msg as json_msg


def pack(data):
    return json_msg.Json(bytes=msgpack.packb(data))


def unpack(message):
    return msgpack.unpackb(message.bytes, encoding="utf-8")


class PackedJson(json_msg.Json):

    def __init__(self, data=None):
        self.data = data

    def set_data(self, data):
        self.bytes = msgpack.packb(data)

    def get_data(self):
        return msgpack.unpackb(self.bytes, encoding="utf-8")

    data = property(get_data, set_data)

    def __str__(self):
        return str(self.data)

    def __repr__(self):
        return("{name}({data})".format(name=self.__class__.__name__, data=repr(self.data)))
