// Unseen Project By 20240301


#include "Character/UnseenAnimInstance.h"

void UUnseenAnimInstance::AnimNotify_BackAttackEnd()
{
	OnBackAttackEnd.Broadcast();
}
