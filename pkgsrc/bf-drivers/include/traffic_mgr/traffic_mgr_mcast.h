/*******************************************************************************
 *  Copyright (C) 2024 Intel Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions
 *  and limitations under the License.
 *
 *
 *  SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/


#ifndef __TRAFFIC_MGR_MCAST_INTF_H__
#define __TRAFFIC_MGR_MCAST_INTF_H__

#include <mc_mgr/mc_mgr_types.h>
#include <traffic_mgr/traffic_mgr_types.h>

/**
 * @file traffic_mgr_mcast.h
 * \brief Details multicast specific APIs.
 */

/**
 * @addtogroup tm-mcast
 * @{
 *  Description of APIs for Traffic Manager application
 *  to program multicast traffic FIFO sizes.
 */

/**
 * Set the input FIFO arbitration mode to strict priority or weighted round
 * robin.  Note that if strict priority is enabled on a FIFO, all FIFOs higher
 * will also be enabled for strict priority.  For example, to set FIFO 1 as
 * strict priority, 2 and 3 must also be strict priority.
 *
 * @param[in] dev               The ASIC id.
 * @param[in] pipe_bmap         Pipe bit mask. Check ASIC manual to find maximum
 *                              of pipes.
 * @param[in] fifo              The FIFO to configure, must be 0, 1, 2 or 3.
 *                              Check ASIC manual to find maximum number of
 *                              fifos per pipe.
 * @param[in] use_strict_pri    If @c true, use strict priority.  If @c false,
 *                              use weighted round robin.
 * @return                      Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_arb_mode_set(bf_dev_id_t dev,
                                       uint8_t pipe_bmap,
                                       int fifo,
                                       bool use_strict_pri);

/**
 * Set the input FIFO arbitration weights used by the weighted round robin
 * arbitration mode.
 *
 * @param[in] dev               The ASIC id.
 * @param[in] pipe_bmap         Pipe bit mask. Check ASIC manual to find maximum
 *                              of pipes.
 * @param[in] fifo              The FIFO to configure, must be 0, 1, 2 or 3.
 *                              Check ASIC capabilites to find maximum number of
 *                              fifos.
 * @param[in] weight            The weight assigned to FIFO.
 * @return                      Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_wrr_weight_set(bf_dev_id_t dev,
                                         uint8_t pipe_bmap,
                                         int fifo,
                                         uint8_t weight);

/**
 * Set multicast fifo to iCoS mapping.
 *
 * @param[in] dev               The ASIC id.
 * @param[in] pipe_bmap         Pipe bit mask. Check ASIC manual to find maximum
 *                              of pipes.
 * @param[in] fifo              The FIFO to configure, must be 0, 1, 2 or 3.
 *                              Check ASIC manual to find maximum number of
 *                              fifos per pipe.
 * @param[in] icos_bmap         iCoS bit map.
 * @return                      Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_icos_mapping_set(bf_dev_id_t dev,
                                           uint8_t pipe_bmap,
                                           int fifo,
                                           uint8_t icos_bmap);

/**
 * Get multicast fifo to iCoS mapping.
 *
 * @param[in] dev               The ASIC id.
 * @param[in] pipe              Pipe number. Check ASIC manual to find maximum
 *                              of pipes.
 * @param[in] fifo              The FIFO id.
 *                              Check ASIC manual to find maximum number of
 *                              fifos per pipe
 * @param[out] icos_bmap        iCoS bit map.
 * @return                      Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_icos_mapping_get(bf_dev_id_t dev,
                                           bf_dev_pipe_t pipe,
                                           int fifo,
                                           uint8_t *icos_bmap);

/**
 * Set the input FIFO depth.  Sum of all four sizes cannot exceed 8192,
 * additionally, each size must be a multiple of 8.
 *
 * @param[in] dev               The ASIC id.
 * @param[in] pipe_bmap         Pipe bit mask. Check ASIC manual to find maximum
 *                              of pipes.
 * @param[in] fifo              The FIFO to configure, must be 0, 1, 2 or 3.
 *                              Check ASIC manual to find maximum number of
 *                              fifos per pipe.
 * @param[in] size              The size assigned to FIFO.
 * @return                      Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_depth_set(bf_dev_id_t dev,
                                    uint8_t pipe_bmap,
                                    int fifo,
                                    int size);

/**
 * Get the input FIFO arbitration mode to strict priority or weighted round
 * robin.  Note that if strict priority is enabled on a FIFO, all FIFOs higher
 * must also be enabled for strict priority.  For example, to set FIFO 1 as
 * strict priority, 2 and 3 must also be strict priority.
 *
 * @param[in] dev               The ASIC id.
 * @param[in] pipe              Pipe number. Check ASIC manual to find maximum
 *                              of pipes.
 * @param[in] fifo              The FIFO id.
 *                              Check ASIC manual to find maximum number of
 *                              fifos per pipe.
 * @param[out] use_strict_pri   If @c true, arbitration mode is strict priority.
 *                              If @c false, arbitration is weighted round
 *                              robin.
 * @return Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_arb_mode_get(bf_dev_id_t dev,
                                       bf_dev_pipe_t pipe,
                                       int fifo,
                                       bool *use_strict_pri);

/**
 * Get the input FIFO arbitration weights used by the weighted round robin
 * arbitration mode.
 *
 * @param[in] dev               The ASIC id.
 * @param[in] pipe              Pipe number. Check ASIC manual to find maximum
 *                              of pipes.
 * @param[in] fifo              The FIFO id.
 *                              Check ASIC manual to find maximum number of
 *                              fifos per pipe.
 * @param[out] weight           The weight assigned to FIFO.
 * @return                      Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_wrr_weight_get(bf_dev_id_t dev,
                                         bf_dev_pipe_t pipe,
                                         int fifo,
                                         uint8_t *weight);

/**
 * Get the input FIFO depth.
 *
 * @param[in] dev               The ASIC id.
 * @param[in] pipe              Pipe number. Check ASIC manual to find maximum
 *                              of pipes.
 * @param[in] fifo              The FIFO id.
 *                              Check ASIC manual to find maximum number of
 *                              fifos per pipe.
 * @param[out] size             The size assigned to FIFO 0.
 * @return                      Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_depth_get(bf_dev_id_t dev,
                                    bf_dev_pipe_t pipe,
                                    int fifo,
                                    int *size);

/**
 * Get default multicast fifo to iCoS mapping.
 *
 * @param[in] dev               The ASIC id.
 * @param[in] pipe              Pipe number. Check ASIC manual to find maximum
 *                              of pipes.
 * @param[in] fifo              The FIFO id.
 *                              Check ASIC manual to find maximum number of
 *                              fifos per pipe
 * @param[out] icos_bmap        iCoS bit map.
 * @return                      Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_icos_mapping_get_default(bf_dev_id_t dev,
                                                   bf_dev_pipe_t pipe,
                                                   int fifo,
                                                   uint8_t *icos_bmap);

/**
 * Get the default input FIFO arbitration mode to strict priority or weighted
 * round robin.
 *
 * @param[in] dev               The ASIC id.
 * @param[in] pipe              Pipe number. Check ASIC manual to find maximum
 *                              of pipes.
 * @param[in] fifo              The FIFO id.
 *                              Check ASIC manual to find maximum number of
 *                              fifos per pipe.
 * @param[out] use_strict_pri   If @c true, arbitration mode is strict priority.
 *                              If @c false, arbitration is weighted round
 *                              robin.
 * @return Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_arb_mode_get_default(bf_dev_id_t dev,
                                               bf_dev_pipe_t pipe,
                                               int fifo,
                                               bool *use_strict_pri);

/**
 * Get the default input FIFO arbitration weights used by the weighted round
 * robin arbitration mode.
 *
 * @param[in] dev               The ASIC id.
 * @param[in] pipe              Pipe number. Check ASIC manual to find maximum
 *                              of pipes.
 * @param[in] fifo              The FIFO id.
 *                              Check ASIC manual to find maximum number of
 *                              fifos per pipe.
 * @param[out] weight           The weight assigned to FIFO.
 * @return                      Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_wrr_weight_get_default(bf_dev_id_t dev,
                                                 bf_dev_pipe_t pipe,
                                                 int fifo,
                                                 uint8_t *weight);

/**
 * Get the default input FIFO depth.
 *
 * @param[in] dev               The ASIC id.
 * @param[in] pipe              Pipe number. Check ASIC manual to find maximum
 *                              of pipes.
 * @param[in] fifo              The FIFO id.
 *                              Check ASIC manual to find maximum number of
 *                              fifos per pipe.
 * @param[out] size             The size assigned to FIFO 0.
 * @return                      Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_depth_get_default(bf_dev_id_t dev,
                                            bf_dev_pipe_t pipe,
                                            int fifo,
                                            int *size);

/* @} */

#endif
