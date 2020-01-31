// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"
AHealthPickUp::AHealthPickUp() {
	stats.key = "health";
	stats.val = 5;
}

FStatPickUp AHealthPickUp::GetStat()
{
	return stats;
}

bool AHealthPickUp::Initialize()
{
	return false;
}
