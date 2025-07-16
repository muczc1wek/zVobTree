namespace GOTHIC_NAMESPACE {
	
	//get recursive children
	void GetChildrenPFX(zCTree<zCVob>* node, zCVob* pickedVob, zCVob* globalParent)
	{
		zCVob* vob = node->GetData();

		if (vob)
		{
			zCParticleFX* m_pPfx = vob->CastTo<zCParticleFX>();

			if (m_pPfx)
			{
				m_pPfx->StopEmitterOutput();
				m_pPfx->m_bVisualNeverDies = false;

			}

			auto visual = vob->GetVisual();

			if (visual)
			{
				if (auto part = visual->CastTo<zCParticleFX>())
				{
					part->StopEmitterOutput();
					part->m_bVisualNeverDies = false;
				}

			}

		}

		node = node->GetFirstChild();

		while (node != NULL)
		{
			GetChildrenPFX(node, pickedVob, globalParent);
			node = node->GetNextChild();
		}
	}

	// checks if level is loaded
	bool IsWorldReadyOrLoaded(bool checkPlayer = true)
	{
		bool result = false;

		bool playerCheck = true;

		if (checkPlayer)
		{
			if (!player || !player->GetHomeWorld())
			{
				playerCheck = false;
			}
		}

		if (playerCheck && ogame && ogame->GetWorld())
		{
			result = true;
		}

		return result;
	}

	enum InsertVobTreeResult {
		INSERT_FAILED,
		INSERT_GLOBAL,
		INSERT_PARENT
	};

	// inserts vobtree into world tree
	InsertVobTreeResult InsertVobTree(zSTRING path, zSTRING parentName) 
    {
		zoptions->ChangeDir(DIR_WORLD);

		zCWorld* world = ogame->GetWorld();

		if (!world)
		{
			return INSERT_FAILED;
		}

		zCVob* pParent = NULL;

		if (parentName.Length() > 0)
		{
			pParent = world->SearchVobByName(parentName);
		}

		zCVob* vob = ogame->GetWorld()->MergeVobSubtree(path, pParent, zCWorld::zWLD_LOAD_MERGE_ADD);

		if (!vob)
		{
			return INSERT_FAILED;
		}

		if (auto wpVob = dynamic_cast<zCVobWaypoint*>(vob))
		{
			auto wp = zfactory->CreateWaypoint();
			wp->Init(wpVob);
			wp->SetName(wpVob->objectName);
			ogame->GetWorld()->wayNet->InsertWaypoint(wp);
		}
		return pParent != NULL ? INSERT_PARENT : INSERT_GLOBAL;
	}
}