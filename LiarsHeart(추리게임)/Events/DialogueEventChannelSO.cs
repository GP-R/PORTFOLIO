using UnityEngine;
using UnityEngine.Events;
using DS.ScriptableObjects;

[CreateAssetMenu(menuName = "Events/Dialogue Event Channel")]
public class DialogueEventChannelSO : ScriptableObject
{
	public event UnityAction<DSDialogueSO> OnEventRaised;

	public void RaiseEvent(DSDialogueSO value)
	{
		if (OnEventRaised != null)
			OnEventRaised.Invoke(value);
	}
}
