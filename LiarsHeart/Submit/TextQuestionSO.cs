using UnityEngine;

[CreateAssetMenu(fileName = "TextQuestionSO", menuName = "Submit/TextQuestion")]
public class TextQuestionSO : QuestionNodeSO
{
    [Tooltip("����")]
    [SerializeField] private string answer = default;
    public string Answer { get => answer; }
}
