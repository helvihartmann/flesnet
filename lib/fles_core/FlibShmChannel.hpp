#pragma once

#include "RingBufferReadInterface.hpp"
#include "RingBuffer.hpp"
#include "RingBufferView.hpp"
#include "MicrosliceDescriptor.hpp"
#include <algorithm>

#include "shm_channel_client.hpp"

/// Wrapper around FLIB shared memory channel.
class FlibShmChannel : public InputBufferReadInterface
{
public:
    /// The FlibShmChannel constructor.
    FlibShmChannel(shm_channel_client* channel);

    FlibShmChannel(const FlibShmChannel&) = delete;
    void operator=(const FlibShmChannel&) = delete;

    virtual ~FlibShmChannel();

    virtual RingBufferView<volatile uint8_t>& data_buffer() override
    {
        return *data_buffer_view_;
    }

    virtual RingBufferView<volatile fles::MicrosliceDescriptor>&
    desc_buffer() override
    {
        return *desc_buffer_view_;
    }

    virtual DualRingBufferIndex get_write_index() override;

    virtual void set_read_index(DualRingBufferIndex new_read_index) override;

private:
    shm_channel_client* channel_;

    std::unique_ptr<RingBufferView<volatile uint8_t>> data_buffer_view_;
    std::unique_ptr<RingBufferView<volatile fles::MicrosliceDescriptor>>
        desc_buffer_view_;
};
