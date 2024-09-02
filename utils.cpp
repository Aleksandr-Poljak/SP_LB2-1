#include "SP_LB2-1.h";

SECURITY_ATTRIBUTES createBaseScurityAttributes()
{
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = nullptr;
	sa.bInheritHandle = FALSE;
	
	return sa;
}