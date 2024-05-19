using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New MapSO", menuName = "Map/Map")]
public class MapSO : ScriptableObject
{
    [Tooltip("��� ����Ʈ")]
    [SerializeField] private List<PlaceSO> places;
    public List<PlaceSO> Places { get => places; }
}
