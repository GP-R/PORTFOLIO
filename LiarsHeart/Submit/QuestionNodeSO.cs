using UnityEngine;

public abstract class QuestionNodeSO : ScriptableObject
{
    [Tooltip("문제 번호")]
    [SerializeField] private int id = default;
    public int Id { get => id; }

    [Tooltip("문제 설명")]
    [SerializeField] private string description = default;
    public string Description { get => description; }
}