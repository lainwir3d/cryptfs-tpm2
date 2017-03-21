/*
 * Internal header
 *
 * Copyright (c) 2016, Wind River Systems, Inc.
 * All rights reserved.
 *
 * See "LICENSE" for license terms.
 *
 * Author:
 *	  Lans Zhang <jia.zhang@windriver.com>
 */

#ifndef __INTERNAL_H__
#define __INTERNAL_H__

#include <cryptfs_tpm2.h>

/* The authorization password for the primary key */
#define CRYPTFS_TPM2_PRIMARY_KEY_SECRET		"H31i05"

/* The authorization password for the passphrase */
#define CRYPTFS_TPM2_PASSPHRASE_SECRET		"h31i05"

struct session_complex {
	TPMI_SH_AUTH_SESSION session_handle;

	TPMS_AUTH_COMMAND sessionData;
	TPMS_AUTH_COMMAND *sessionDataArray[1];
	TSS2_SYS_CMD_AUTHS sessionsData;

	TPMS_AUTH_RESPONSE sessionDataOut;
	TPMS_AUTH_RESPONSE *sessionDataOutArray[1];
	TSS2_SYS_RSP_AUTHS sessionsDataOut;
};

extern TSS2_SYS_CONTEXT *cryptfs_tpm2_sys_context;

int
util_digest_size(TPMI_ALG_HASH hash_alg, UINT16 *alg_size);

void
password_session_create(struct session_complex *s, char *auth_password);

int
policy_session_create(struct session_complex *s, TPM_SE type,
                      TPMI_ALG_HASH hash_alg);

void
policy_session_destroy(struct session_complex *s);

void
policy_auth_set(TPMS_AUTH_COMMAND *session, TPMI_SH_AUTH_SESSION handle,
		char *auth_password);

int
pcr_policy_extend(TPMI_DH_OBJECT session_handle, TPML_PCR_SELECTION *pcrs,
		  TPMI_ALG_HASH policy_digest_alg);

int
password_policy_extend(TPMI_DH_OBJECT session_handle);

int
capability_read_public(TPMI_DH_OBJECT handle, TPM2B_PUBLIC *public_out);

int
sha1_digest(BYTE *data, UINT16 data_len, BYTE *hash);

int
hash_digest(TPMI_ALG_HASH hash_alg, BYTE *data, UINT16 data_len, BYTE *hash);

#endif	/* __INTERNAL_H__ */