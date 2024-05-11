using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New SubmitSO", menuName = "Submit/SubmitSO")]
public class SubmitSO : ScriptableObject
{
    [Tooltip("Submit Name")]
    [SerializeField] private string submitPrefabName;
    public string SubmitPrefabName { get => submitPrefabName; }
}
