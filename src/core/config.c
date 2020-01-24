/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <config.h>

void config_adjust_to_va(struct config *config, uint64_t phys)
{
    for (int i = 0; i < config->vmlist_size; i++) {
        config->vmlist[i].image.load_addr =
            config->vmlist[i].image.load_addr + phys;
        config->vmlist[i].platform.regions =
            (void *)config->vmlist[i].platform.regions + (uint64_t)config;
        config->vmlist[i].platform.devs =
            (void *)config->vmlist[i].platform.devs + (uint64_t)config;

        for (int j = 0; j < config->vmlist[i].platform.dev_num; j++) {
            config->vmlist[i].platform.devs[j].interrupts =
                (void *)config->vmlist[i].platform.devs[j].interrupts +
                (uint64_t)config;
        }

        config->vmlist[i].platform.arch.smmu.smmu_groups =
            (void *)config->vmlist[i].platform.arch.smmu.smmu_groups +
            (uint64_t)config;
    }

    // TODO: maybe it might be needed an arch version of this method
}
