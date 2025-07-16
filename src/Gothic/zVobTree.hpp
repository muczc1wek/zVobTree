namespace GOTHIC_NAMESPACE::zVobTree {

    void Remove(zSTRING& vobName)
	{
        static NH::Logger* log = NH::CreateLogger("zVobTree::Remove");

		if (!IsWorldReadyOrLoaded(false)) return ;

		if (vobName.Length() > 0)
		{
			zCVob* pVob = ogame->GetWorld()->SearchVobByName(vobName);

			if (pVob)
			{
				zCTree<zCVob>* tree = pVob->globalVobTreeNode;
				GetChildrenPFX(tree, pVob, pVob);
				ogame->GetWorld()->RemoveVobSubtree(pVob);
                log->Info("Vobtree '{0}' removed", vobName.ToChar());
			}
            else
            {
                log->Warning("Vob '{0}' not found", vobName.ToChar());
            }
		}
	}


	void Insert(zSTRING& path) {
        static NH::Logger* log = NH::CreateLogger("zVobTree::Insert");

        InsertVobTreeResult result = InsertVobTree(path, "");

		if (result == INSERT_FAILED) {
            log->Warning("File '{0}' not found", path.ToChar());
        } 
        else {
            log->Info("Vobtree '{0}' inserted", path.ToChar());
        }
	}


	void InsertParent(zSTRING& path, zSTRING& parentName) {
        static NH::Logger* log = NH::CreateLogger("zVobTree::InsertParent");

        InsertVobTreeResult result = InsertVobTree(path, parentName);

        switch (result) {
            case INSERT_PARENT:
                log->Info("Vobtree '{0}' inserted into '{1}'", path.ToChar(), parentName.ToChar());
                break;
            case INSERT_GLOBAL:
                log->Warning("Vobtree '{0}' inserted globally, parent '{1}' was not found", path.ToChar(), parentName.ToChar());
                break;
            case INSERT_FAILED:
                log->Warning("File '{0}' not found", path.ToChar());
                break; 
        }
    }
}