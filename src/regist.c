

void
regist_team(GROUP *cup)
{
	char group_names[AMOUNT_OF_GROUPS];
	char group;

	group_names = get_group_names(group_names);

	group = get_group(group_names);
	while (get_amount_of_registered_teams(cup, group) > 3) {
		printf("The group %c is already complete\n", group);
		
		group = get_group(group_names);
	}

	get_team(cup, group);
}
