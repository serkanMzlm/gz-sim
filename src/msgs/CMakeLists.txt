PROTOBUF_GENERATE_CPP(PROTO_PRIVATE_SRC PROTO_PRIVATE_HEADERS
  peer_info.proto
  peer_control.proto
  performer_affinity.proto
  simulation_step.proto
)

set(PROTO_PRIVATE_SRC ${PROTO_PRIVATE_SRC} PARENT_SCOPE)
set(PROTO_PRIVATE_HEADERS ${PROTO_PRIVATE_HEADERS} PARENT_SCOPE)

add_custom_target(gz-sim_private_msgs
  DEPENDS ${PROTO_PRIVATE_SRC}
)
