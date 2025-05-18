/// Inserts a vobtree into the game world
///
/// @param filePath path to the vobtree file relative to the Worlds directory
func void VobTree_Insert(var string filePath) {};

/// Inserts a vobtree into specified parent vob
///
/// @param filePath path to the vobtree file relative to the Worlds directory
/// @param vobName name of the parent vob
func void VobTree_InsertParent(var string filePath, var string vobName) {};

/// Removes a vobtree from the game world
///
/// @param vobName name of the parent vob
func void VobTree_Remove(var string vobName) {};