#ifndef THIRD_PARTY_GRPC_SRC_CORE_TELEMETRY_TCP_TELEMETRY_H_
#define THIRD_PARTY_GRPC_SRC_CORE_TELEMETRY_TCP_TELEMETRY_H_

#include "src/core/telemetry/histogram.h"
#include "src/core/telemetry/instrument.h"

namespace grpc_core {

class TcpTelemetryDomain final : public InstrumentDomain<TcpTelemetryDomain> {
 public:
  using Backend = HighContentionBackend;
  static constexpr absl::string_view kName = "tcp_connection_metrics";
  static constexpr auto kLabels =
      Labels("network.local.address", "network.local.port",
             "network.remote.address", "network.remote.port");

  static inline const auto kMinRtt =
      RegisterHistogram<ExponentialHistogramShape>(
          "min_rtt", "Minimum round trip time of a connection in seconds",
          "{s}", 1024, 20);
  static inline const auto kDeliveryRate =
      RegisterHistogram<ExponentialHistogramShape>(
          "delivery_rate",
          "TCP's most recent measure of the connection's "
          "\"non-app-limited\" throughput.",
          "By/s", 1024, 20);
  static inline const auto kPacketsSent = RegisterCounter(
      "packets_sent",
      "Total packets sent by TCP including retransmissions and spurious "
      "retransmissions.",
      "{packet}");
  static inline const auto kPacketsRetransmitted = RegisterCounter(
      "packets_retransmitted",
      "Total packets sent by TCP except those sent for the first time.",
      "{packet}");
  static inline const auto kPacketsSpuriousRetransmitted = RegisterCounter(
      "packets_spurious_retransmitted",
      "Total packets retransmitted by TCP that were later found to be "
      "unnecessary.",
      "{packet}");
  static inline const auto kRecurringRetransmits = RegisterCounter(
      "recurring_retransmits",
      "The number of times the latest TCP packet was retransmitted due to "
      "expiration of TCP retransmission timer (RTO), and not acknowledged at "
      "the time the connection was closed.",
      "{packet}");
  static inline const auto kBytesSent = RegisterCounter(
      "bytes_sent",
      "Total bytes sent by TCP including retransmissions and spurious "
      "retransmissions.",
      "By");
  static inline const auto kBytesRetransmitted = RegisterCounter(
      "bytes_retransmitted",
      "Total bytes sent by TCP except those sent for the first time.", "By");
  static inline const auto kConnectionCount = RegisterUpDownCounter(
      "connection_count", "Number of active TCP connections.", "{connection}");
  static inline const auto kSyscallWrites = RegisterCounter(
      "syscall_writes",
      "The number of times we invoked the sendmsg (or sendmmsg) syscall and "
      "wrote data to the TCP socket.",
      "{syscall}");
  static inline const auto kWriteSize =
      RegisterHistogram<ExponentialHistogramShape>(
          "write_size", "The number of bytes offered to each syscall_write.",
          "By", 1024, 20);
  static inline const auto kSyscallReads = RegisterCounter(
      "syscall_reads",
      "The number of times we invoked the recvmsg (or recvmmsg or zero copy "
      "getsockopt) syscall and read data from the TCP socket.",
      "{syscall}");
  static inline const auto kReadSize =
      RegisterHistogram<ExponentialHistogramShape>(
          "read_size", "The number of bytes received by each syscall_read.",
          "By", 1024, 20);
  static inline const auto kSenderLatency =
      RegisterHistogram<ExponentialHistogramShape>(
          "sender_latency",
          "Time taken by the TCP socket to write the first byte of a write "
          "onto the NIC.",
          "s", 1024, 20);
  static inline const auto kTransferLatency1k =
      RegisterHistogram<ExponentialHistogramShape>(
          "transfer_latency_1k",
          "Time taken to transmit the first 1024 bytes of a write.", "s", 1024,
          20);
  static inline const auto kTransferLatency8k =
      RegisterHistogram<ExponentialHistogramShape>(
          "transfer_latency_8k",
          "Time taken to transmit the first 8196 bytes of a write.", "s", 1024,
          20);
  static inline const auto kTransferLatency64k =
      RegisterHistogram<ExponentialHistogramShape>(
          "transfer_latency_64k",
          "Time taken to transmit the first 65536 bytes of a write.", "s", 1024,
          20);
  static inline const auto kTransferLatency256k =
      RegisterHistogram<ExponentialHistogramShape>(
          "transfer_latency_256k",
          "Time taken to transmit the first 262144 bytes of a write.", "s",
          1024, 20);
  static inline const auto kTransferLatency2m =
      RegisterHistogram<ExponentialHistogramShape>(
          "transfer_latency_2m",
          "Time taken to transmit the first 2097152 bytes of a write.", "s",
          1024, 20);
};

};  // namespace grpc_core

#endif  // THIRD_PARTY_GRPC_SRC_CORE_TELEMETRY_TCP_TELEMETRY_H_
