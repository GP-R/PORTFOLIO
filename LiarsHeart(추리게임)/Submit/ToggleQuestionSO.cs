using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "ToggleQuestionSO", menuName = "Submit/ToggleQuestion")]
public class ToggleQuestionSO : QuestionNodeSO
{
    [Tooltip("����")]
    [SerializeField] private List<int> answers = new List<int>();
    public List<int> Answers { get => answers; }
}