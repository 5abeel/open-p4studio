################################################################################
 #  Copyright (C) 2024 Intel Corporation
 #
 #  Licensed under the Apache License, Version 2.0 (the "License");
 #  you may not use this file except in compliance with the License.
 #  You may obtain a copy of the License at
 #
 #  http://www.apache.org/licenses/LICENSE-2.0
 #
 #  Unless required by applicable law or agreed to in writing,
 #  software distributed under the License is distributed on an "AS IS" BASIS,
 #  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 #  See the License for the specific language governing permissions
 #  and limitations under the License.
 #
 #
 #  SPDX-License-Identifier: Apache-2.0
################################################################################

"""
Base classes for test cases

Tests will usually inherit from one of these classes to have the controller
and/or dataplane automatically set up.
"""

import os
import logging
import unittest

import ptf
from ptf.base_tests import BaseTest
from ptf import config
import ptf.dataplane as dataplane

################################################################
#
# Thrift interface base tests
#
################################################################

import diag_rpc.diag_rpc as diag_rpc
from diag_rpc.ttypes import *
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol


class ThriftInterface(BaseTest):

    def setUp(self):
        BaseTest.setUp(self)

        # Set up thrift client and contact server
        self.transport = TSocket.TSocket('localhost', 9096)
        self.transport = TTransport.TBufferedTransport(self.transport)
        self.protocol = TBinaryProtocol.TBinaryProtocol(self.transport)

        self.client = diag_rpc.Client(self.protocol)
        self.transport.open()

    def tearDown(self):
        if config["log_dir"] is not None:
            self.dataplane.stop_pcap()
        BaseTest.tearDown(self)
        self.transport.close()


class ThriftInterfaceDataPlane(ThriftInterface):
    """
    Root class that sets up the thrift interface and dataplane
    """
    def setUp(self):
        ThriftInterface.setUp(self)
        self.dataplane = ptf.dataplane_instance
        self.dataplane.flush()
        if config["log_dir"] is not None:
            filename = os.path.join(config["log_dir"], str(self)) + ".pcap"
            self.dataplane.start_pcap(filename)

    def tearDown(self):
        if config["log_dir"] is not None:
            self.dataplane.stop_pcap()
        ThriftInterface.tearDown(self)
