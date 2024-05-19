using UnityEngine;
using UnityEngine.Events;

[CreateAssetMenu(menuName = "Events/Submit Event Channel")]
public class SubmitEventChannelSO : ScriptableObject
{
    public event UnityAction<QuestionNodeSO> OnEventRaised;

    public void RaiseEvent(QuestionNodeSO submit)
    {
        if (OnEventRaised != null)
            OnEventRaised.Invoke(submit);
    }
}