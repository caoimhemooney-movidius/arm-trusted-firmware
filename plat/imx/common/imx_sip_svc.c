/*
 * Copyright (c) 2015-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <common/debug.h>
#include <common/runtime_svc.h>
#include <lib/pmf/pmf.h>
#include <tools_share/uuid.h>
#include <imx_sip_svc.h>

static int32_t imx_sip_setup(void)
{
	return 0;
}

static uintptr_t imx_sip_handler(unsigned int smc_fid,
			u_register_t x1,
			u_register_t x2,
			u_register_t x3,
			u_register_t x4,
			void *cookie,
			void *handle,
			u_register_t flags)
{
	switch (smc_fid) {
#if (defined(PLAT_IMX8QM) || defined(PLAT_IMX8QX))
	case  IMX_SIP_SRTC:
		return imx_srtc_handler(smc_fid, handle, x1, x2, x3, x4);
	case  IMX_SIP_CPUFREQ:
		SMC_RET1(handle, imx_cpufreq_handler(smc_fid, x1, x2, x3));
		break;
#endif
	default:
		WARN("Unimplemented i.MX SiP Service Call: 0x%x\n", smc_fid);
		SMC_RET1(handle, SMC_UNK);
		break;
	}
}

/* Define a runtime service descriptor for fast SMC calls */
DECLARE_RT_SVC(
		imx_sip_svc,
		OEN_SIP_START,
		OEN_SIP_END,
		SMC_TYPE_FAST,
		imx_sip_setup,
		imx_sip_handler
);
