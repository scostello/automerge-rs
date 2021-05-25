#ifndef automerge_h
#define automerge_h

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <stdint.h>
#include <stdbool.h>

typedef struct Backend Backend;

typedef struct SyncState SyncState;

/**
 * A sequence of byte buffers that are contiguous in memory
 * The C caller allocates one of these with `create_buffs`
 * and passes it into each API call. This prevents allocating memory
 * on each call. The struct fields are just the constituent fields in a Vec
 * This is used for returning data to C.
 */
typedef struct {
  /**
   * A pointer to the bytes
   */
  uint8_t *data;
  /**
   * The total number of bytes across all buffers
   */
  uintptr_t data_len;
  /**
   * The total allocated memory `data` points to
   * This is needed so Rust can free `data`
   */
  uintptr_t data_cap;
  /**
   * The length (in bytes) of each buffer
   */
  uintptr_t *lens;
  /**
   * The number of buffers
   */
  uintptr_t lens_len;
  /**
   * The total allocated memory `buf_lens` points to
   * This is needed so Rust can free `buf_lens`
   */
  uintptr_t lens_cap;
} Buffers;

/**
 * Similar to `Buffers`, except this struct
 * should be allocated / freed by C.
 * Used to pass an the C-equivalent of `Vec<Vec<u8>>` to Rust
 */
typedef struct {
  uint8_t *data;
  uintptr_t data_len;
  uintptr_t *lens;
  uintptr_t lens_len;
} CBuffers;

/**
 * # Safety
 * This should be called with a valid pointer to a `Backend`
 * `CBuffers` should be non-null & have valid fields.
 */
intptr_t automerge_apply_changes(Backend *backend, Buffers *buffs, const CBuffers *cbuffs);

/**
 * # Safety
 * This should be called with a valid pointer to a `Backend`
 * and a valid pointer to a `Buffers``
 */
intptr_t automerge_apply_local_change(Backend *backend, Buffers *buffs, const char *request);

/**
 * # Safety
 * This should be called with a valid pointer to a `Backend`
 */
intptr_t automerge_clone(Backend *backend, Backend **new_);

/**
 * Create a `Buffers` struct to store return values
 */
Buffers automerge_create_buffs(void);

/**
 * # Safety
 * This must me called with a valid pointer to a change and the correct len
 */
intptr_t automerge_decode_change(Backend *backend, Buffers *buffs, const uint8_t *change, uintptr_t len);

/**
 * # Safety
 * `encoded_state_[ptr|len]` must be the address & length of a byte array
 */
intptr_t automerge_decode_sync_state(Backend *backend,
                                     const uint8_t *encoded_state_ptr,
                                     uintptr_t encoded_state_len,
                                     SyncState **sync_state);

/**
 * # Safety
 * This must me called with a valid pointer to a JSON string of a change
 */
intptr_t automerge_encode_change(Backend *backend, Buffers *buffs, const char *change);

/**
 * # Safety
 * Must be called with a pointer to a valid Backend, sync_state, and buffs
 */
intptr_t automerge_encode_sync_state(Backend *backend, Buffers *buffs, SyncState *sync_state);

/**
 * # Safety
 * This must be called with a valid backend pointer
 */
const char *automerge_error(Backend *backend);

/**
 * # Safety
 * This must be called with a valid backend pointer
 */
void automerge_free(Backend *backend);

/**
 * Free the memory a `Buffers` struct points to
 */
intptr_t automerge_free_buffs(Buffers *buffs);

/**
 * # Safety
 * Must be called with a valid backend pointer
 * sync_state must be a valid pointer to a SyncState
 * Returns an `isize` indicating the length of the binary message
 * (-1 if there was an error, 0 if there is no message)
 */
intptr_t automerge_generate_sync_message(Backend *backend, Buffers *buffs, SyncState *sync_state);

/**
 * # Safety
 * This must be called with a valid backend pointer,
 * binary must be a valid pointer to `hashes` hashes
 */
intptr_t automerge_get_changes(Backend *backend, Buffers *buffs, const uint8_t *bin, uintptr_t hashes);

/**
 * # Safety
 * This must be called with a valid pointer to a `Backend`
 * and a valid C String
 */
intptr_t automerge_get_changes_for_actor(Backend *backend, Buffers *buffs, const char *actor);

/**
 * # Safety
 * This must be called with a valid backend pointer
 */
intptr_t automerge_get_heads(Backend *backend, Buffers *buffs);

/**
 * # Safety
 * This must be called with a valid backend pointer,
 * binary must be a valid pointer to len bytes
 */
intptr_t automerge_get_missing_deps(Backend *backend, Buffers *buffs, const uint8_t *bin, uintptr_t len);

/**
 * # Safety
 * This should be called with a valid pointer to a `Backend`
 * and a valid pointer to a `Buffers``
 */
intptr_t automerge_get_patch(Backend *backend, Buffers *buffs);

Backend *automerge_init(void);

/**
 * # Safety
 * This must be called with a valid pointer to len bytes
 */
Backend *automerge_load(const uint8_t *data, uintptr_t len);

/**
 * # Safety
 * This should be called with a valid pointer to a `Backend`
 * and a valid pointers to a `CBuffers`
 */
intptr_t automerge_load_changes(Backend *backend, const CBuffers *cbuffs);

/**
 * # Safety
 * Must be called with a valid backend pointer
 * sync_state must be a valid pointer to a SyncState
 * `encoded_msg_[ptr|len]` must be the address & length of a byte array
 */
intptr_t automerge_receive_sync_message(Backend *backend,
                                        Buffers *buffs,
                                        SyncState *sync_state,
                                        const uint8_t *encoded_msg_ptr,
                                        uintptr_t encoded_msg_len);

/**
 * # Safety
 * This should be called with a valid pointer to a `Backend`
 */
intptr_t automerge_save(Backend *backend, Buffers *buffs);

/**
 * # Safety
 * sync_state must be a valid pointer to a SyncState
 */
void automerge_sync_state_free(SyncState *sync_state);

SyncState *automerge_sync_state_init(void);

/**
 * # Safety
 * Must be called with a valid buffs pointer
 * Copy a single buff from a Buffers to a destination.
 * The destination must be large enough to hold all of dest
 */
uintptr_t util_read_buffs(const Buffers *buffs, uintptr_t idx, uint8_t *dest);

/**
 * # Safety
 * Must be called with a valid buffs pointer
 * Copy a single buff from a Buffers to a destination & null terminate it
 * The destination must be large enough to hold all of dest
 */
void util_read_buffs_str(Buffers *buffs, uintptr_t idx, uint8_t *dest);

#endif /* automerge_h */
