# Copyright CERN and copyright holders of ALICE O2. This software is distributed
# under the terms of the GNU General Public License v3 (GPL Version 3), copied
# verbatim in the file "COPYING".
#
# See http://alice-o2.web.cern.ch/license for full licensing information.
#
# In applying this license CERN does not waive the privileges and immunities
# granted to it by virtue of its status as an Intergovernmental Organization or
# submit itself to any jurisdiction.

o2_add_library(MCHWorkflow
               SOURCES src/DataDecoderSpec.cxx src/PreClusterFinderSpec.cxx src/ClusterFinderOriginalSpec.cxx
               TARGETVARNAME targetName
               PUBLIC_LINK_LIBRARIES O2::Framework O2::DPLUtils O2::MCHRawDecoder Boost::program_options
                                     O2::MCHRawImplHelpers RapidJSON::RapidJSON O2::MCHMappingInterface O2::MCHPreClustering
                                     O2::MCHMappingImpl3 O2::MCHRawElecMap O2::MCHBase O2::MCHClustering)

o2_add_executable(
        file-to-digits-workflow
        SOURCES src/file-to-digits-workflow.cxx
        COMPONENT_NAME mch
        PUBLIC_LINK_LIBRARIES O2::Framework O2::DPLUtils O2::MCHRawDecoder Boost::program_options
                              O2::MCHRawImplHelpers O2::MCHMappingInterface
                              O2::MCHMappingImpl3 O2::MCHRawElecMap O2::MCHBase)

o2_add_executable(
        cru-page-reader-workflow
        SOURCES src/cru-page-reader-workflow.cxx
        COMPONENT_NAME mch
        PUBLIC_LINK_LIBRARIES O2::Framework O2::DetectorsRaw O2::DPLUtils Boost::program_options)

o2_add_executable(
        digits-sink-workflow
        SOURCES src/digits-sink-workflow.cxx
        COMPONENT_NAME mch
        PUBLIC_LINK_LIBRARIES O2::Framework O2::DPLUtils Boost::program_options O2::MCHBase)

o2_add_executable(
        raw-to-digits-workflow
        SOURCES src/raw-to-digits-workflow.cxx
        COMPONENT_NAME mch
        PUBLIC_LINK_LIBRARIES O2::MCHWorkflow)

o2_add_executable(
        digits-to-preclusters-workflow
        SOURCES src/digits-to-preclusters-workflow.cxx
        COMPONENT_NAME mch
        PUBLIC_LINK_LIBRARIES O2::MCHWorkflow)

o2_add_executable(
        digits-reader-workflow
        SOURCES src/DigitSamplerSpec.cxx src/digits-reader-workflow.cxx
        COMPONENT_NAME mch
        PUBLIC_LINK_LIBRARIES O2::MCHWorkflow)

o2_add_executable(
        preclusters-sink-workflow
        SOURCES src/PreClusterSinkSpec.cxx src/preclusters-sink-workflow.cxx
        COMPONENT_NAME mch
        PUBLIC_LINK_LIBRARIES O2::MCHWorkflow)

o2_add_executable(
        preclusters-to-clusters-original-workflow
        SOURCES src/preclusters-to-clusters-original-workflow.cxx
        COMPONENT_NAME mch
        PUBLIC_LINK_LIBRARIES O2::MCHWorkflow)

o2_add_executable(
        clusters-sink-workflow
        SOURCES src/ClusterSinkSpec.cxx src/clusters-sink-workflow.cxx
        COMPONENT_NAME mch
        PUBLIC_LINK_LIBRARIES O2::MCHWorkflow)
