#pragma once

namespace Auth
{
	int SignUser(const Entity::User& acc);
	int LogUser(const Entity::User& acc);
}