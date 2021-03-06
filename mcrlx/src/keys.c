/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmckinno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 13:33:22 by tmckinno          #+#    #+#             */
/*   Updated: 2017/10/23 13:33:24 by tmckinno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mcrlx.h"

int	on_key_press(int kc, t_evloop loop)
{
	t_event ev;

	IF_RET((kc >= MAX_KC), -1);
	SET_KEY(loop->keys, kc);
	ERR_CNR((ev = create_event(EV_KEY)), NULL, -1);
	ev->kc = kc;
	ev->state = 1;
	enqueue(loop->events, ev, 1);
	return (0);
}

int	on_key_release(int kc, t_evloop loop)
{
	t_event ev;

	IF_RET((kc >= MAX_KC), -1);
	CLR_KEY(loop->keys, kc);
	ERR_CNR((ev = create_event(EV_KEY)), NULL, -1);
	ev->kc = kc;
	enqueue(loop->events, ev, 1);
	return (0);
}

int	on_mouse_press(int btn, int x, int y, t_evloop loop)
{
	t_event ev;

	IF_RET((btn >= MAX_MOUSE), -1);
	SET_KEY(loop->mouse, btn);
	ERR_CNR((ev = create_event(EV_KEY)), NULL, -1);
	ev->kc = btn;
	ev->state = 1;
	ev->x = x;
	ev->y = y;
	enqueue(loop->events, ev, 1);
	return (0);
}

int	on_mouse_release(int btn, int x, int y, t_evloop loop)
{
	t_event ev;

	IF_RET((btn >= MAX_MOUSE), -1);
	CLR_KEY(loop->mouse, btn);
	ERR_CNR((ev = create_event(EV_MOUSE)), NULL, -1);
	ev->kc = btn;
	ev->x = x;
	ev->y = y;
	enqueue(loop->events, ev, 1);
	return (0);
}

int	on_mouse_motion(int x, int y, t_evloop loop)
{
	t_event ev;

	if (x >= 0 && x < loop->window->width && y >= 0 && y < loop->window->height)
	{
		ERR_CNR((ev = create_event(EV_MOTION)), NULL, -1);
		ev->mpos_prev[0] = loop->mouse[MOUSE_X];
		ev->mpos_prev[1] = loop->mouse[MOUSE_Y];
		loop->mouse[MOUSE_X] = x - (loop->window->width >> 1);
		loop->mouse[MOUSE_Y] = (y - (loop->window->height >> 1)) * -1;
		ev->mpos_cur[0] = loop->mouse[MOUSE_X];
		ev->mpos_cur[1] = loop->mouse[MOUSE_Y];
		enqueue(loop->events, ev, 1);
	}
	return (0);
}
