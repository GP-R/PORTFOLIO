using UnityEngine;

public abstract class QuestionNodeSO : ScriptableObject
{
    [Tooltip("���� ��ȣ")]
    [SerializeField] private int id = default;
    public int Id { get => id; }

    [Tooltip("���� ����")]
    [SerializeField] private string description = default;
    public string Description { get => description; }
}