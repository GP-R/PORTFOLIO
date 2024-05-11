using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New ChapterSO", menuName = "GameData/Chapter")]
public class ChapterSO : ScriptableObject
{
    [Header("Character Data")]
    [SerializeField] private CharacterData characterData;
    public CharacterData CharacterData { get => characterData; }

    [Header("Map Data")]
    [SerializeField] private MapSO mapData;
    public MapSO MapData { get => mapData; }

    [Tooltip("Submit Data")]
    [SerializeField] private SubmitSO submitData;
    public SubmitSO SubmitData { get => submitData; }
}
