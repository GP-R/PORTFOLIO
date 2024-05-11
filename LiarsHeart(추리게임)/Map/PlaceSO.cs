using UnityEngine;

[CreateAssetMenu(fileName = "New PlaceSO", menuName = "Map/Place")]
public class PlaceSO : ScriptableObject
{
    [SerializeField] private string name;
    public string Name { get => name; }

    [SerializeField] private GameObject placePrefab;
    public GameObject PlacePrefab { get => placePrefab; }
}
