static u16 s_nextPort = 49152;

// ------------------------------------------------------------------------------------------------
u16 NetEphemeralPort()
{
    // TODO - check for collisions with active connections.
    return s_nextPort++;
}