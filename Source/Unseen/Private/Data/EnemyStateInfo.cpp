// Unseen Project By 20240301


#include "Data/EnemyStateInfo.h"

FEnemyDetectionStateInfo* UEnemyStateInfo::FindEnemyDetectionStateInfo(EEnemyDetectionState NewState)
{
	return EnemyDetectionStateInformation.Find(NewState);
}
